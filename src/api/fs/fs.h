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

#ifndef FS_H_
#define FS_H_

#include "../../../deps/v8/include/v8.h"
#include "../../common/macros.h"
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fstream>

#ifdef _WIN32
#include <windows.h>
#elif __APPLE__
#include <sys/param.h>
#include <sys/sysctl.h>
#else
#include <unistd.h>

#endif

using namespace v8;

namespace JSK{
	namespace FS{
		int Build(const FunctionCallbackInfo<Value>& args);
		void FileExists(const FunctionCallbackInfo<Value>& args);
		bool FileExists(const char* filename);
		Handle<String> ReadFile(Isolate* isolate, const char* name);
		void FileInfo(const FunctionCallbackInfo<Value>& args);
		void Open(const FunctionCallbackInfo<Value>& args);
		void DeleteFile(const FunctionCallbackInfo<Value>& args);
		void ReadDir(const FunctionCallbackInfo<Value>& args);
		void Write(const FunctionCallbackInfo<Value>& args);
		void Rename(const FunctionCallbackInfo<Value>& args);
		Handle<Object> File_DB();

		// DB object
		void DBSave(const FunctionCallbackInfo<Value>& args);
	}
}

#endif // FS_H_