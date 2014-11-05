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

#include "os.h"

using namespace v8;

namespace JSK{
	namespace OS{
		/*
			var os = {
				platform: [string],
				cpus: [int],
				launch: [Function](programName)
			}

			Todos:
				http://msdn.microsoft.com/en-us/library/windows/desktop/ms724426(v=vs.85).aspx
		*/
		int Build(const FunctionCallbackInfo<Value>& args){
			Isolate* isolate = args.GetIsolate();
			Handle<Object> global = isolate->GetCurrentContext()->Global();
			Handle<Object> OSObject = global->Get(String::NewFromUtf8(isolate, "os"))->ToObject();
			GetPlatform(isolate, OSObject);
			GetCpus(isolate, OSObject);
			GetComputerName(isolate, OSObject);
			args.GetReturnValue().Set(OSObject);
			return 1;
		}

		void GetPlatform(Isolate* isolate, Handle<Object>& var){
			const char* platform;
			#ifdef __APPLE__
			platform = "Apple";
			#endif
			#ifdef __MINGW32__
			platform = "Windows";
			#endif
			#ifdef __linux__
			platform = "Linux";
			#endif
			var->Set(String::NewFromUtf8(isolate, "platform"), String::NewFromUtf8(isolate, platform));
		}

		// Code from http://www.cprogramming.com/snippets/source-code/find-the-number-of-cpu-cores-for-windows-mac-or-linux
		void GetCpus(Isolate* isolate, Handle<Object>& var){
			int numOfCpus;
			#ifdef WIN32
			    SYSTEM_INFO info;
			    GetSystemInfo(&sysinfo);
			    numOfCpus = sysinfo.dwNumberOfProcessors;
			#elif MACOS
			    int nm[2];
			    size_t len = 4;
			    uint32_t count;
			 
			    nm[0] = CTL_HW; nm[1] = HW_AVAILCPU;
			    sysctl(nm, 2, &count, &len, NULL, 0);
			 
			    if(count < 1) {
			    nm[1] = HW_NCPU;
			    sysctl(nm, 2, &count, &len, NULL, 0);
			    if(count < 1) { count = 1; }
			    }
			    numOfCpus = count;
			#else
			    numOfCpus = sysconf(_SC_NPROCESSORS_ONLN);
			#endif
			var->Set(String::NewFromUtf8(isolate, "cpus"), Integer::New(isolate, numOfCpus));
		}

		void GetComputerName(Isolate* isolate, Handle<Object>& var){
			char name[MAXHOSTNAMELEN + 1];
			
			#ifdef __APPLE__
			gethostname(name, sizeof(name));
			#endif
			#ifdef __MINGW32__
			const char* computerName[MAX_COMPUTERNAME_LENGTH + 1];
			DWORD size = sizeof(computerName) / sizeof(computerName[0]);
			GetComputerName(computerName, &size);
			name = computerName;
			#endif

			name[sizeof(name) - 1] = '\0';
			var->Set(String::NewFromUtf8(isolate, "hostname"), String::NewFromUtf8(isolate, name));
		}
	}
}