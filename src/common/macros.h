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

#ifndef MACROS_H_
#define MACROS_H_

#include "../../deps/v8/include/v8.h"
#include <string>
using namespace v8;

namespace JSK{

	inline const char* GET_VERSION(){
		std::string major = "0";
		std::string minor = "1";
		std::string patch = "0";
		std::string version = major + "." + minor + "." + patch;
		return version.c_str();
	}
	#define GET_VERSION JSK::GET_VERSION

	// Macro to string
	inline const char* TO_STRING(Local<Value>& val){
		String::Utf8Value param1(val);
	    std::string str = std::string(*param1); 
	    char* module = new char[str.size() + 1];
		std::copy(str.begin(), str.end(), module);
		module[str.size()] = '\0'; // don't forget the terminating 0
		return module;
	}
	#define TO_STRING JSK::TO_STRING

	// Macro for converting string to char
	inline const char* TO_CHAR(std::string str) {
		char * writable = new char[str.size() + 1];
		std::copy(str.begin(), str.end(), writable);
		writable[str.size()] = '\0'; // don't forget the terminating 0

		// don't forget to free the string after finished using it
		return writable;
	}
	#define TO_CHAR JSK::TO_CHAR

	inline void REPORT(TryCatch* try_catch){
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope handle_scope(isolate);

		Local<Value> val = try_catch->Exception();	
		const char* exception_string = TO_STRING(val);
		Handle<Message> message = try_catch->Message();

		if (message.IsEmpty())
			fprintf(stderr, "%s\n", exception_string);
		else {
			Local<Value> filename = message->GetScriptOrigin().ResourceName();

			const char* filename_string = TO_CHAR(TO_STRING(filename));
			int linenum = message->GetLineNumber();
			fprintf(stderr, "%s:%i: %s\n", filename_string, linenum, exception_string);

			// Print line of source code.
			Local<Value> sourceline = message->GetSourceLine();
			const char* sourceline_string = TO_CHAR(TO_STRING(sourceline));
			fprintf(stderr, "%s\n", sourceline_string);

			int start = message->GetStartColumn();
			for (int i = 0; i < start; i++) {
			  fprintf(stderr, " ");
			}
			int end = message->GetEndColumn();
			for (int i = start; i < end; i++) {
			  fprintf(stderr, "^");
			}
			fprintf(stderr, "\n");

			Local<Value> stack_trace = try_catch->StackTrace();
			if (!stack_trace->IsUndefined() || !stack_trace->IsNull()) {
			  const char* stack_trace_string = TO_CHAR(TO_STRING(stack_trace));
			  fprintf(stderr, "%s\n", stack_trace_string);
			  delete stack_trace_string;
			}

			delete filename_string;
			delete sourceline_string;
		}
	}
	#define REPORT JSK::REPORT

	// Macro for throwing an exception
	inline void THROW(const char* msg) {
		printf("%s\n", msg);
		Isolate* isolate = Isolate::GetCurrent();
	  if (!isolate){
	  	isolate = Isolate::New();
	  	isolate->Enter();
	  }
	  isolate->ThrowException(String::NewFromUtf8(isolate, msg));
	  TryCatch try_catch;
	  REPORT(&try_catch);
	}
	#define THROW JSK::THROW

	// Macro for getting the isolate
	inline Isolate* ISOLATE(){
		Isolate* isolate = Isolate::GetCurrent();
	  if (!isolate){
	  	return NULL;
	  }
	  return isolate;
	}
	#define ISOLATE JSK::ISOLATE
}

#endif