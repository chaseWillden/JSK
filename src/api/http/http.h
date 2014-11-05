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

#ifndef HTTP_H_
#define HTTP_H_

#include "../../../deps/v8/include/v8.h"
#include "../../common/macros.h"
#include <stdio.h>
#include "../../../deps/curl/include/curl/curl.h"
#include "../../../deps/curl/include/curl/easy.h"
#include "../../../deps/curl/include/curl/curlbuild.h"

#include <sstream>
#include <iostream>
#include <string>


#ifdef _WIN32

#elif __APPLE__

#else

#endif

using namespace v8;

namespace JSK{
	namespace HTTP{
		int Build(const FunctionCallbackInfo<Value>& args);
		void Request(const FunctionCallbackInfo<Value>& args);
	}
}

#endif // HTTP_H_