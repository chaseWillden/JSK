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

#ifndef WINDOW_H_
#define WINDOW_H_

#include "../../../deps/v8/include/v8.h"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

#if __APPLE__

#if __OBJC__

#else

#endif //__OBJC__
#endif

namespace JSK{
	namespace WINDOW{
		int Build(const v8::FunctionCallbackInfo<v8::Value>& args);
		void Alert(const v8::FunctionCallbackInfo<v8::Value>& args);

	}
}

#endif // WINDOW_H_