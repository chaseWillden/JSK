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

#include "fs.h"

using namespace v8;

namespace JSK{
    namespace FS{
        /*
            var fs = {
                exists: [Function](path),
                open: [Function](path),
                fileInfo: [Function](path),
                deleteFile: [Function](path),
                readDir: [Function](dir),
                inDir: [Function](dir, file),
                isDir: [Function](dir),
                rename: [Function](old, new),
                write: [Function](path, data)
            }
        */
        int Build(const FunctionCallbackInfo<Value>& args){
            Isolate* isolate = args.GetIsolate();
            Handle<Object> global = isolate->GetCurrentContext()->Global();
            Handle<Object> FSObject = global->Get(String::NewFromUtf8(isolate, "fs"))->ToObject();

            // Populate the object components
            FSObject->Set(String::NewFromUtf8(isolate, "exists"), Function::New(isolate, FileExists));
            FSObject->Set(String::NewFromUtf8(isolate, "open"), Function::New(isolate, Open));
            FSObject->Set(String::NewFromUtf8(isolate, "fileInfo"), Function::New(isolate, FileInfo));
            FSObject->Set(String::NewFromUtf8(isolate, "deleteFile"), Function::New(isolate, DeleteFile));
            FSObject->Set(String::NewFromUtf8(isolate, "readDir"), Function::New(isolate, ReadDir));
            FSObject->Set(String::NewFromUtf8(isolate, "write"), Function::New(isolate, Write));
            FSObject->Set(String::NewFromUtf8(isolate, "rename"), Function::New(isolate, Rename));
            args.GetReturnValue().Set(FSObject);
            return 1;
        }

        void FileExists(const FunctionCallbackInfo<Value>& args){           
            if (args.Length() != 1 || !args[0]->IsString())
                return THROW(args, "Invalid Arguments");

            Local<Value> val = args[0];
            std::string filename(TO_STRING(val));
            args.GetReturnValue().Set(Boolean::New(args.GetIsolate(), FileExists(filename))); 
        }

        bool FileExists(std::string filename){
            struct stat buf;
            return stat(filename.c_str(), &buf) != -1;
        }

        void FileInfo(const FunctionCallbackInfo<Value>& args){
            if (args.Length() != 1 || !args[0]->IsString())
                return THROW(args, "Invalid Arguments");

            Local<Value> val = args[0];
            std::string filename(TO_STRING(val));
            struct stat buf;
            stat(filename.c_str(), &buf);

            // Create return object
            Local<Object> rObj = Object::New(args.GetIsolate());
            rObj->Set(String::NewFromUtf8(args.GetIsolate(), "hardLinks"), Integer::New(args.GetIsolate(), buf.st_nlink));
            rObj->Set(String::NewFromUtf8(args.GetIsolate(), "size"), Integer::New(args.GetIsolate(), buf.st_size));
            rObj->Set(String::NewFromUtf8(args.GetIsolate(), "accessed"), Date::New(args.GetIsolate(), buf.st_atime));
            rObj->Set(String::NewFromUtf8(args.GetIsolate(), "modified"), Date::New(args.GetIsolate(), buf.st_mtime));
            rObj->Set(String::NewFromUtf8(args.GetIsolate(), "created"), Date::New(args.GetIsolate(), buf.st_ctime));
            bool isDir = buf.st_mode & S_IFDIR;
            rObj->Set(String::NewFromUtf8(args.GetIsolate(), "isDir"), Boolean::New(args.GetIsolate(), isDir));

            args.GetReturnValue().Set(rObj); 
        }

        void Open(const FunctionCallbackInfo<Value>& args){
            if (args.Length() < 1 || !args[0]->IsString())
                return THROW(args, "Invalid Arguments");

            Local<Value> val = args[0];
            std::string filename(TO_STRING(val));
            Handle<String> contents = ReadFile(args.GetIsolate(), TO_CHAR(filename));
            if (contents->Length() < 1)
                return THROW(args, "Empty File");
            args.GetReturnValue().Set(contents);
        }

        void DeleteFile(const FunctionCallbackInfo<Value>& args){
            if (args.Length() < 1 || !args[0]->IsString())
                return THROW(args, "Invalid Arguments");

            Local<Value> val = args[0];
            std::string filename(TO_STRING(val));
            bool removed = false;

            if (remove(TO_CHAR(filename)) == 0){
                removed = true;
            }

            args.GetReturnValue().Set(Boolean::New(args.GetIsolate(), removed));
        }

        // Reads a file into a v8 string.
        Handle<String> ReadFile(Isolate* isolate, const char* name) {;
          FILE* file = fopen(name, "rb");
          if (file == NULL) return Handle<String>();
          fseek(file, 0, SEEK_END);
          int size = ftell(file);
          rewind(file);

          char* chars = new char[size + 1];
          chars[size] = '\0';
          for (int i = 0; i < size;) {
            int read = static_cast<int>(fread(&chars[i], 1, size - i, file));
            i += read;
          }
          fclose(file);
          Handle<String> result = String::NewFromUtf8(isolate, chars, String::kNormalString, size);
          delete[] chars;
          return result;
        }

        void ReadDir(const FunctionCallbackInfo<Value>& args){
            if (args.Length() < 1 || !args[0]->IsString())
                return THROW(args, "Invalid Arguments");

            Local<Value> val = args[0];
            std::string filename(TO_STRING(val));
            DIR *dir;
            struct dirent *ent;
            if ((dir = opendir (TO_CHAR(filename))) != NULL) {
            /* print all the files and directories within directory */
                Local<Array> dirObj = Array::New(args.GetIsolate());
                int i = 0;
                while ((ent = readdir (dir)) != NULL) {
                    dirObj->Set(Number::New(args.GetIsolate(), i++), String::NewFromUtf8(args.GetIsolate(), ent->d_name));
                }
                closedir (dir);

                // Return value
                args.GetReturnValue().Set(dirObj);
            } 
            else {
                /* could not open directory */
                THROW(args, "Unable to open dir");
            }
        }

        void Write(const FunctionCallbackInfo<Value>& args){
            if (args.Length() < 2 || !args[0]->IsString())
                return THROW(args, "Invalid Arguments");

            Local<Value> val = args[0];
            std::string filename(TO_STRING(val));
            Local<Value> contents = args[1];
            std::string str(TO_STRING(contents));
            std::ofstream file(TO_CHAR(filename));
            file.open(TO_CHAR(filename));
            file << str;
            file.close();
        }

        void Rename(const FunctionCallbackInfo<Value>& args){
            if (args.Length() < 2 || !args[0]->IsString() || !args[1]->IsString())
                return THROW(args, "Invalid Arguments");

            Local<Value> old = args[0];
            std::string oldname(TO_STRING(old));
            Local<Value> n = args[1];
            std::string newname(TO_STRING(n));

            int success = rename(TO_CHAR(oldname), TO_CHAR(newname));
            if (success == 0)
                args.GetReturnValue().Set(Boolean::New(args.GetIsolate(), success == 0));
            else
                THROW(args, &"Error code: " [success]);     
        }
    }
}