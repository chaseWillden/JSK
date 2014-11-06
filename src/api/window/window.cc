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

#include "window.h"

using namespace v8;

namespace JSK{
	namespace WINDOW{
		/*
			var window = {

			}

		*/
		int Build(const FunctionCallbackInfo<Value>& args){
			Isolate* isolate = args.GetIsolate();
			Handle<Object> global = isolate->GetCurrentContext()->Global();
			Handle<Object> WindowObj = global->Get(String::NewFromUtf8(isolate, "window"))->ToObject();

			WindowObj->Set(String::NewFromUtf8(isolate, "alert"), Function::New(isolate, Alert));
			args.GetReturnValue().Set(WindowObj);
			return 1;
		}

		void Alert(const FunctionCallbackInfo<Value>& args){
			
		}
	}
}