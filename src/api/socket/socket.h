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

#ifndef SOCKET_H_
#define SOCKET_H_

#include "../../../deps/v8/include/v8.h"
#include "../../common/macros.h"
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <vector>

#ifdef _WIN32

#elif __APPLE__

#else
#include <unistd.h>

#endif
#define MAXHOSTNAMELEN 256

using namespace v8;

namespace JSK{
	namespace SOCKET{
		int Build(const FunctionCallbackInfo<Value>& args);

		class Socket
		{
		public:
			Socket(const FunctionCallbackInfo<Value>& args);
			~Socket();	
			int port;
			const char* listenMsg;
			const char* writeMsg;
			Handle<Function> callback;
			Handle<Object> getCallback;
			bool hasGet;

			void Close();
			void Write(const FunctionCallbackInfo<Value>& args);
			void Listen(const FunctionCallbackInfo<Value>& args);
		};

		class Request
		{
		public:
			Request();
			~Request();
			void AddHeader(const char* headerline);
			std::vector<const char*> headers;
			void Format();
			Handle<Object> obj;
		};

		void CreateSocketObject(const FunctionCallbackInfo<Value>& args);
		void CloseWrapper(const FunctionCallbackInfo<Value>& args);
		void GetWrapper(const FunctionCallbackInfo<Value>& args);
		void WriteWrapper(const FunctionCallbackInfo<Value>& args);
		void ListenWrapper(const FunctionCallbackInfo<Value>& args);
		void GenerateListen(const FunctionCallbackInfo<Value>& args);
		void doprocessing (int sock, const FunctionCallbackInfo<Value>& args);
	}
}

#endif // SOCKET_H_