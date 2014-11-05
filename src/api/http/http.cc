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

#include "http.h"

using namespace v8;

namespace JSK{
	namespace HTTP{
		/*
			var http = {
				request: [Function](url || obj)
			}
		*/
		int Build(const FunctionCallbackInfo<Value>& args){
			Isolate* isolate = args.GetIsolate();
			Handle<Object> global = isolate->GetCurrentContext()->Global();
			Handle<Object> HTTPObject = global->Get(String::NewFromUtf8(isolate, "http"))->ToObject();

			// Populate the object components
			HTTPObject->Set(String::NewFromUtf8(isolate, "request"), Function::New(isolate, Request));
			args.GetReturnValue().Set(HTTPObject);
			return 1;
		}

		size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) {
		    std::string data((const char*) ptr, (size_t) size * nmemb);
		    *((std::stringstream*) stream) << data << std::endl;
		    return size * nmemb;
		}

		void Request(const FunctionCallbackInfo<Value>& args){
			Local<Value> v8Url;
			Local<Value> v8encoding;

			// Assign an empty string to callback
			Local<Value> v8Callback = String::NewFromUtf8(args.GetIsolate(), "");
			if (args[0]->IsObject()){
				Local<Object> options = args[0]->ToObject();

				// Url
				v8Url = options->Get(String::NewFromUtf8(args.GetIsolate(), "url"));
				if (v8Url->IsUndefined() || v8Url->IsNull())
					return THROW(args, "No uri specified");

				// Encoding
				v8encoding = options->Get(String::NewFromUtf8(args.GetIsolate(), "encoding"));
				if (v8encoding->IsUndefined() || v8encoding->IsNull())
					v8encoding = String::NewFromUtf8(args.GetIsolate(), "deflate");

				v8Callback = options->Get(String::NewFromUtf8(args.GetIsolate(), "callback"));
			}
			else if (args[0]->IsString()){
				v8Url = args[0]->ToString();
				v8encoding = String::NewFromUtf8(args.GetIsolate(), "deflate");
			}
			else{
				return THROW(args, "Invalid Arguments");	
			}

			std::string url(TO_STRING(v8Url));
			std::string encoding(TO_STRING(v8encoding));

			CURL *curl;
			curl = curl_easy_init();

			// Options
			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		    /* example.com is redirected, so we tell libcurl to follow redirection */
		    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1); //Prevent "longjmp causes uninitialized stack frame" bug
		    curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, TO_CHAR(encoding));


		    std::stringstream out;
		    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);
		    /* Perform the request, res will get the return code */
		    CURLcode res = curl_easy_perform(curl);
		    /* Check for errors */
		    if (res != CURLE_OK)
		    	return THROW(args, curl_easy_strerror(res));

		    // Encoding
			Handle<Value> argv[1];
			argv[0] = String::NewFromUtf8(args.GetIsolate(), out.str().c_str());

			if (v8Callback->IsNull() || v8Callback->IsFunction()){
				Handle<Function> callback = Handle<Function>::Cast(v8Callback);
				callback->Call(args.GetIsolate()->GetCurrentContext()->Global(), 1, argv);
			}				
			else
				args.GetReturnValue().Set(String::NewFromUtf8(args.GetIsolate(), out.str().c_str()));
		}
	}
}