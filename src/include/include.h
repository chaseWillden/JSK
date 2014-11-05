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
// Notes: http://stackoverflow.com/questions/15731699/how-to-bind-a-stdfunction-to-javascript-v8

#ifndef INCLUDE_H_
#define INCLUDE_H_

#include "../../deps/v8/include/v8.h"

namespace JSK{
	void BuildEnv(v8::Isolate* isolate, v8::Handle<v8::ObjectTemplate> global);	
	void BuildEnv(v8::Isolate* isolate, v8::Handle<v8::Object> global);
	void CallFunc(const v8::FunctionCallbackInfo<v8::Value>& args);
	void IncludeFunc(const v8::FunctionCallbackInfo<v8::Value>& args);

	typedef int (*FnPtr)(const v8::FunctionCallbackInfo<v8::Value>& args);
}

#endif // INCLUDE_H_