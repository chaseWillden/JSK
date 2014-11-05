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

#ifndef ENV_H_
#define ENV_H_

#include "../../deps/v8/include/v8.h"
#include "../include/include.h"
#include "format/format.h"
#include "globals/globals.h"
#include "../api/fs/fs.h"
#include "macros.h"
#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifdef _WIN32

#elif __APPLE__

#else

#endif

using namespace v8;

namespace JSK{
	class Env
	{
	public:
		Env();
		~Env();
		Isolate* Init(int argc, char* argv[]);
		Isolate* GetIsolate();
		Local<Value> result;
		Handle<Context> CreateContext(Isolate* isolate);
		Handle<Context> CreateGlobals();
		Handle<Context> GetContext();
		bool Execute(bool globalContext, Handle<String> code, Handle<Value> name);
		void Report(TryCatch* try_catch);
		Local<Value> ReadAndExecute(bool globalContext, const char* filename);
	
	private:
		Isolate* mainIsolate;
	};

	class ShellArrayBufferAllocator : public ArrayBuffer::Allocator {
	 public:
	  virtual void* Allocate(size_t length) {
	    void* data = AllocateUninitialized(length);
	    return data == NULL ? data : memset(data, 0, length);
	  }
	  virtual void* AllocateUninitialized(size_t length) { return malloc(length); }
	  virtual void Free(void* data, size_t) { free(data); }
	};

	void ExitProg(const FunctionCallbackInfo<Value>& args);
}

#endif // ENV_H_