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

#include "shell.h"

using namespace v8;

namespace JSK{
	namespace SHELL{
		/*
			var shell = {
				execute: [Function](str),
				print: [Function](str)
			}
		*/
		int Build(const FunctionCallbackInfo<Value>& args){
			Isolate* isolate = args.GetIsolate();
			Handle<Object> global = isolate->GetCurrentContext()->Global();
			Handle<Object> FormatObject = global->Get(String::NewFromUtf8(isolate, "shell"))->ToObject();

			// Attach the functions to the object
			FormatObject->Set(String::NewFromUtf8(isolate, "execute"), Function::New(isolate, Child));
			FormatObject->Set(String::NewFromUtf8(isolate, "print"), Function::New(isolate, Print));
			args.GetReturnValue().Set(FormatObject);
			return 1;
		}

		void Child(const FunctionCallbackInfo<Value>& args){
			if (args.Length() != 1 || !args[0]->IsString())
				THROW( "Invalid Arguments");
			else{
				Local<Value> val = args[0];
				std::string cmd(TO_STRING(val));
				FILE* pipe = popen(TO_CHAR(cmd), "r");
		    if (!pipe)
		    	THROW( "Unable to open shell");
		    char buffer[128];
		    std::string result = "";
		    while(!feof(pipe)) {
		    	if(fgets(buffer, 128, pipe) != NULL)
		    		result += buffer;
		    }
		    printf("%s\n", TO_CHAR(result));
		    pclose(pipe);
		    args.GetReturnValue().Set(String::NewFromUtf8(args.GetIsolate(), TO_CHAR(result)));
			}
		}

		void Print(const FunctionCallbackInfo<Value>& args){
			if (args.Length() != 1 || !args[0]->IsString())
				THROW( "Invalid Arguments");
			else{
				Local<Value> val = args[0];
				std::string str(TO_STRING(val));
				printf("%s\n", TO_CHAR(str));
			}
		}	
	}
}