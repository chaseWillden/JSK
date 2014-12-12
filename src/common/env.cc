// Copyright Chase Willden and the JSK Authors.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to permit
// persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
// USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "env.h"

using namespace v8;

namespace JSK{

	Env::Env(){
		this->mainIsolate = Isolate::GetCurrent();	
	}

	Env::~Env(){}

	Isolate* Env::Init(int argc, char* argv[]){
		V8::InitializeICU();
		V8::Initialize();
		if (argc > 0)
			V8::SetFlagsFromCommandLine(&argc, argv, true);
  	ShellArrayBufferAllocator array_buffer_allocator;
  	V8::SetArrayBufferAllocator(&array_buffer_allocator);
  	this->mainIsolate = Isolate::New();
  	return this->mainIsolate;
	}

	Isolate* Env::GetIsolate(){
		return this->mainIsolate;
	}

	Handle<Context> Env::CreateContext(Isolate* isolate){
		return Context::New(isolate);
	}

	Handle<Context> Env::GetContext(){
		return this->GetIsolate()->GetCurrentContext();
	}

	Handle<Context> Env::CreateGlobals(){
		Isolate* isolate = this->GetIsolate();
		// Create a template for the global object.
		Handle<ObjectTemplate> global = ObjectTemplate::New(isolate);
		global->Set(String::NewFromUtf8(isolate, "exit"), FunctionTemplate::New(isolate, ExitProg));

		JSK::BuildEnv(isolate, global);
		JSK::GLOBALS::BuildGlobal(isolate, global);

		Handle<Context> context = Context::New(isolate, NULL, global);
		context->Enter();
		this->Execute(true, String::NewFromUtf8(this->GetIsolate(), "include('print');"), String::NewFromUtf8(this->GetIsolate(), "print"));
		return context;
	}

	Local<Value> Env::ReadAndExecute(bool globalContext, const char* filename){
		Isolate* isolate = this->GetIsolate();
		Handle<Context> context;
		if (globalContext)
			context = this->GetContext();
		else
			context = this->CreateContext(isolate);
		context->Enter();

		Handle<String> code = JSK::FS::ReadFile(isolate, filename);
		this->Execute(globalContext, code, String::NewFromUtf8(isolate, filename));
		return this->result;
	}

	bool Env::Execute(bool globalContext, Handle<String> code, Handle<Value> name){
		Handle<Context> context;
		if (globalContext)
			context = this->GetContext();
		else
			context = this->CreateContext(this->GetIsolate());
		context->Enter();

		TryCatch try_catch;
		ScriptOrigin origin(name);
		Handle<Script> script = Script::Compile(code, &origin);
		if (script.IsEmpty()){
			this->Report(&try_catch);
			return false;
		}
		else{
			this->result = script->Run();
			if (this->result.IsEmpty()){
				assert(try_catch.HasCaught());
				this->Report(&try_catch);
				return false;
			}
			else{
				assert(!try_catch.HasCaught());
				if (!this->result->IsUndefined() && this->result->IsObject()){

					// Print the results
					Local<Value> strCode = code;
					std::string resultsStr(TO_STRING(strCode));
					char* resultsChar = const_cast<char*>(TO_CHAR(TO_STRING(strCode)));
					std::string searchStr(resultsChar);
					if (searchStr.find("=") != std::string::npos){
						return true;
					}
					else{
						resultsStr.replace(resultsStr.begin(), resultsStr.end(), ';', ' ');
						std::string pre("print(");
						std::string post(")");
						std::string stitch = pre + resultsStr + post;
						this->Execute(true, String::NewFromUtf8(this->GetIsolate(), stitch.c_str()), String::NewFromUtf8(this->GetIsolate(), "print"));
					}
				}
				return true;
			}
		}
	}

	void Env::Report(TryCatch* try_catch) {
		Isolate* isolate = this->GetIsolate();
		HandleScope handle_scope(isolate);

		Local<Value> val = try_catch->Exception();	
		const char* exception_string = TO_CHAR(TO_STRING(val));
		Handle<Message> message = try_catch->Message();

		if (message.IsEmpty())
			fprintf(stderr, "%s\n", exception_string);
		else {
			Local<Value> filename = message->GetScriptOrigin().ResourceName();

			const char* filename_string = TO_CHAR(TO_STRING(filename));
			int linenum = message->GetLineNumber();
			fprintf(stderr, "%s:%i: %s\n", filename_string, linenum, exception_string);

			// Print line of source code.
			Local<Value> sourceline = message->GetSourceLine();
			const char* sourceline_string = TO_CHAR(TO_STRING(sourceline));
			fprintf(stderr, "%s\n", sourceline_string);

			int start = message->GetStartColumn();
			for (int i = 0; i < start; i++) {
			  fprintf(stderr, " ");
			}
			int end = message->GetEndColumn();
			for (int i = start; i < end; i++) {
			  fprintf(stderr, "^");
			}
			fprintf(stderr, "\n");

			Local<Value> stack_trace = try_catch->StackTrace();
			if (!stack_trace->IsUndefined() || !stack_trace->IsNull()) {
			  const char* stack_trace_string = TO_CHAR(TO_STRING(stack_trace));
			  fprintf(stderr, "%s\n", stack_trace_string);
			  delete stack_trace_string;
			}

			delete filename_string;
			delete sourceline_string;
		}
	}

	void ExitProg(const FunctionCallbackInfo<Value>& args){
		V8::Dispose();
		exit(1);
	}
}