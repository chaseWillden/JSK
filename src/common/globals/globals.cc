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

#include "globals.h"

using namespace v8;

namespace JSK{
	namespace GLOBALS{
		/*
			
		*/
		void BuildGlobal(Isolate* isolate, Handle<ObjectTemplate>& global){
			Handle<ObjectTemplate> shoelace = ObjectTemplate::New(isolate);

			BuildShoelace(isolate, shoelace);

			global->Set(String::NewFromUtf8(isolate, "shoelace"), shoelace);
			global->Set(String::NewFromUtf8(isolate, "setTimeout"), FunctionTemplate::New(isolate, SetTimeOut));
		}

		void BuildShoelace(Isolate* isolate, Handle<ObjectTemplate>& global){
			global->Set(String::NewFromUtf8(isolate, "version"), String::NewFromUtf8(isolate, GET_VERSION()));
		}

		// https://code.google.com/p/v8-juice/source/browse/trunk/src/include/v8/juice/time.h
		void SetTimeOut(const FunctionCallbackInfo<Value>& args){
			if (args.Length() < 1 && args[0]->IsFunction())
				THROW( "Invalid arguments");

		}
	}
}