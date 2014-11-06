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

#include "include.h"
#include "../common/macros.h"
#include "../js_natives.h"
#include "../api/os/os.h"
#include "../api/fs/fs.h"
#include "../api/http/http.h"
#include "../common/format/format.h"
#include "../api/shell/shell.h"
#include "../common/globals/globals.h"
#include "../api/socket/socket.h"
#include "../common/env.h"
#include "../api/window/window.h"
#include <string>
#include <map>

using namespace v8;

namespace JSK{
	void BuildEnv(Isolate* isolate, Handle<ObjectTemplate> global){
		global->Set(String::NewFromUtf8(isolate, "include"), FunctionTemplate::New(isolate, IncludeFunc));
	}

	void BuildEnv(Isolate* isolate, Handle<Object> global){
		global->Set(String::NewFromUtf8(isolate, "include"), Function::New(isolate, IncludeFunc));
	}

	void CallFunc(const char* name, const FunctionCallbackInfo<Value>& args){
		std::map<const char*, FnPtr> ModMap;
		const char* nativeMethods = "os|fs|http|format|shell|socket|window";
	    ModMap["os"] = JSK::OS::Build;
	    ModMap["fs"] = JSK::FS::Build;
	    ModMap["http"] = JSK::HTTP::Build;
	    ModMap["format"] = JSK::FORMAT::Build;
	    ModMap["shell"] = JSK::SHELL::Build;
	    ModMap["socket"] = JSK::SOCKET::Build;
	    ModMap["window"] = JSK::WINDOW::Build;

	    // usage:
	    if (strstr(nativeMethods, name))
	    	ModMap[name](args);
	    else
	    	args.GetReturnValue().Set(args.GetIsolate()->GetCurrentContext()->Global()->Get(String::NewFromUtf8(args.GetIsolate(), name)));
	}

	void IncludeFunc(const FunctionCallbackInfo<Value>& args){
		if (args.Length() != 1 || !args[0]->IsString()){
			args.GetIsolate()->ThrowException(String::NewFromUtf8(args.GetIsolate(), "Bad parameters"));
			return;
		}
		Local<Value> val = args[0];
		const char* module = TO_STRING(val);

		Handle<Value> printObj = args.GetIsolate()->GetCurrentContext()->Global()->Get(String::NewFromUtf8(args.GetIsolate(), "print"));

		bool IsRegisteredModule = false;
		for (int i = 0; natives[i].name; i++){
			if (IsRegisteredModule) break;

			// Creates global function
			if (!printObj->IsObject() && strcmp(natives[i].name, "print") == 0){
				Script::Compile(String::NewFromUtf8(args.GetIsolate(), natives[i].source))->Run();
				IsRegisteredModule = true;
			}

			// returns an object
			else if (strcmp(module, natives[i].name) == 0){
				Local<Context> current = Context::New(args.GetIsolate());
				// Create a new context so you cant acces this outside of the scope
				current->Enter();
				Script::Compile(String::NewFromUtf8(args.GetIsolate(), natives[i].source))->Run();
				CallFunc(natives[i].name, args);
				IsRegisteredModule = true;
				BuildEnv(current->GetIsolate(), current->Global());
				// Don't forget to close it
				current->Exit();
			}				
		}
		// Module error checking
		if (!IsRegisteredModule) {
			JSK::Env env;
			Local<Value> objVal = env.ReadAndExecute(false, module);
			if (objVal->IsUndefined() || objVal->IsNull())
				THROW(args, "Module does not exist");
			else{
				Local<Object> obj = env.GetContext()->Global();
				args.GetReturnValue().Set(obj->Get(String::NewFromUtf8(env.GetIsolate(), "send")));	
			}
		}

		delete[] module;
	}
}