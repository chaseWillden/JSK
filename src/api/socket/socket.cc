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

#include "socket.h"

using namespace v8;

namespace JSK{
	namespace SOCKET{
		/*
			var socket = {

			}
		*/

		Socket* _socket;

		bool isCreated = false;
		Local<Object> global;
		Handle<Object> globalSocketObj;
		Handle<Object> globalResponseObj;
		Handle<Object> globalRequestObj;

		int Build(const FunctionCallbackInfo<Value>& args){
			Isolate* isolate = args.GetIsolate();
			Handle<Object> global = isolate->GetCurrentContext()->Global();
			Handle<Object> SocketObject = global->Get(String::NewFromUtf8(isolate, "socket"))->ToObject();
			Handle<Object> response = SocketObject->Get(String::NewFromUtf8(isolate, "response"))->ToObject();

			SocketObject->Set(String::NewFromUtf8(isolate, "create"), Function::New(isolate, CreateSocketObject));
			SocketObject->Set(String::NewFromUtf8(isolate, "listen"), Function::New(isolate, ListenWrapper));
			SocketObject->Set(String::NewFromUtf8(isolate, "get"), Function::New(isolate, GetWrapper));
			SocketObject->Set(String::NewFromUtf8(isolate, "close"), Function::New(isolate, CloseWrapper));
			response->Set(String::NewFromUtf8(isolate, "write"), Function::New(isolate, WriteWrapper));
			response->Set(String::NewFromUtf8(isolate, "start"), Function::New(isolate, StartWrapper));

			args.GetReturnValue().Set(SocketObject);
			globalResponseObj = response;
			globalSocketObj = SocketObject;
			return 1;
		}

		void StartWrapper(const FunctionCallbackInfo<Value>& args){
			_socket->writeMsg = " ";
		}

		void GetWrapper(const FunctionCallbackInfo<Value>& args){
			if (args.Length() != 1 || !args[0]->IsFunction())
				THROW(args, "Invalid arguments");
			_socket->getCallback = args[0]->ToObject();
			_socket->hasGet = true;
		}

		void CloseWrapper(const FunctionCallbackInfo<Value>& args){
			delete _socket;
		}

		void ListenWrapper(const FunctionCallbackInfo<Value>& args){
			_socket->Listen(args);
		}

		void WriteWrapper(const FunctionCallbackInfo<Value>& args){
			_socket->Write(args);
		}

		void CreateSocketObject(const FunctionCallbackInfo<Value>& args){
			if (!isCreated){
				_socket = new Socket(args);
				isCreated = true;
			}
		}

		Socket::Socket(const FunctionCallbackInfo<Value>& args){
			this->port = 8080;
			this->listenMsg = "Listening...";
			this->writeMsg = " ";
			this->hasGet = false;
		}

		void Socket::Close(){

		}

		void Socket::Listen(const FunctionCallbackInfo<Value>& args){
			if (args.Length() != 3 || !args[0]->IsNumber())
				THROW(args, "Invalid port");

			this->port = args[0]->Int32Value();

			if (args[1]->IsString()){
				Local<Value> msg = args[1];
				this->listenMsg = TO_STRING(msg);
			}

			// var s = h.createServer(function(req,res){print(req);print(res);})
			if (args[2]->IsFunction()){
				_socket->callback = args[2]->ToObject();
				global = args.GetIsolate()->GetCurrentContext()->Global();
				globalSocketObj = global->Get(String::NewFromUtf8(args.GetIsolate(), "socket"))->ToObject()->ToObject();
				globalRequestObj = globalSocketObj->Get(String::NewFromUtf8(args.GetIsolate(), "response"))->ToObject();
				Handle<Value> argv[] = {
					globalRequestObj,
					String::NewFromUtf8(args.GetIsolate(), "")
				};
				if (_socket->callback->IsCallable())
					_socket->callback->CallAsFunction(args.This(), 2, argv);
			}

			GenerateListen(args);
		}

		void Socket::Write(const FunctionCallbackInfo<Value>& args){
			if (args.Length() != 1 && args[0]->IsString())
				THROW(args, "Invalid arguments");

			Local<Value> msg = args[0];
			std::string strMsg = TO_STRING(msg);
			std::string existing(this->writeMsg);
			this->writeMsg = (strMsg + existing).c_str();
		}

		Socket::~Socket(){}

		Request::Request(){

		}

		void Request::AddHeader(const char* headerline){
			this->headers.push_back(headerline);
		}

		void Request::Format(){
			int len = this->headers.size();
			Isolate* isolate = Isolate::GetCurrent();
			this->obj = Object::New(isolate);
			for (int i = 0; i < len; i++){
				char * header;
				char* name;
				bool n = true;
				char* value;
				if (i != 0){
					header = strtok (const_cast<char*>(this->headers[i]), ":");
				}
				else{
					header = strtok (const_cast<char*>(this->headers[i]), " ");
				}
				while (header != NULL) {
					if (n){
						name = header;
						n = false;
					}
					else{
						value = header;
						break;
					};
					if (i != 0)
						header = strtok (NULL, ":");
					else
						header = strtok (NULL, " ");
				}
				if (strlen(value) < 1){
					Local<Value> strName = String::NewFromUtf8(isolate, name);
					Local<Value> strValue = String::NewFromUtf8(isolate, " ");
					this->obj->Set(strName, strValue);
				}
				else{
					Local<Value> strName = String::NewFromUtf8(isolate, name);
					Local<Value> strValue = String::NewFromUtf8(isolate, value);
					this->obj->Set(strName, strValue);
				}
									
			}
		}

		Request::~Request(){}

		void GenerateListen(const FunctionCallbackInfo<Value>& args){
			int port = _socket->port;

			int sockfd, newsockfd, clilen;
		    char buffer[256];
		    struct sockaddr_in serv_addr, cli_addr;
		    int  n;
		    int pid;
		    socklen_t* socketLen;

		    /* First call to socket() function */
		    int yes=1;
			//char yes='1'; // use this under Solaris

		    sockfd = socket(AF_INET, SOCK_STREAM, 0);
		    if (sockfd < 0) 
		    	return THROW(args, "Error opening socket");

		    /* Initialize socket structure */
		    bzero((char *) &serv_addr, sizeof(serv_addr));

		    serv_addr.sin_family = AF_INET;
		    serv_addr.sin_addr.s_addr = INADDR_ANY;
		    serv_addr.sin_port = htons(port);
		 	
		    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
			    THROW(args, "Error opening socket");
			}

		    /* Now bind the host address using bind() call.*/
		    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		    	return THROW(args, "Error on binding");

		    /* Now start listening for the clients, here 
		     * process will go in sleep mode and will wait 
		     * for the incoming connection
		     */
		    if (listen(sockfd,5) != 0)
		    	return THROW(args, "Error Listening");

		    clilen = sizeof(cli_addr);
		    socketLen = (socklen_t*)&clilen;
		    while (1) 
		    {
		    	printf("%s\n", _socket->listenMsg);
		        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, socketLen);
		        if (newsockfd < 0)
		        	return THROW(args, "Error on accept");

		        /* Create child process */
		        pid = fork();
		        if (pid < 0)
		        	return THROW(args, "Error on creating sub process");

		        if (pid == 0)  
		        {
		            /* This is the client process */
		            close(sockfd);
		            doprocessing(newsockfd, args);
		            _exit(0);
		        }
		        else
		        	close(newsockfd);

		    }
		}

		void doprocessing (int sock, const FunctionCallbackInfo<Value>& args)
		{
		    int n;
		    char buffer[256];

		    bzero(buffer,256);

		    Request* request = new Request();

		    n = read(sock,buffer,255);
		    if (n < 0)
			    return THROW(args, "Error reading from socket");

			char* header = strtok(buffer, "\n\r");

			while(header != NULL){
				request->AddHeader(header);
				header = strtok(NULL, "\n\r");
			}

			request->Format();

			if (_socket->hasGet){
				Handle<Value> argv[] = {
					globalResponseObj,
					request->obj
				};
				// Call the get method now
				_socket->getCallback->CallAsFunction(args.This(), 2, argv);
			}
			else{
				Handle<Value> argv[] = {
					globalRequestObj,
					request->obj
				};
				if (_socket->callback->IsCallable()){
					_socket->callback->CallAsFunction(args.This(), 2, argv);
				}
			}

			n = write(sock, _socket->writeMsg, strlen(_socket->writeMsg));
				
			
		    if (n < 0) 
		    	return THROW(args, "Error writing to socket");

		    delete request;
		    delete header;
		}
	}
}