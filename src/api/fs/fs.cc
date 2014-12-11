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
                write: [Function](path, data),
                gui: [Function](),
                db: {
                    save: [Function](name, path)
                }
            }
        */

        /*
        * Like all new objects, int Build is the first function called. 
        * This is used to build the object
        */
        int Build(const FunctionCallbackInfo<Value>& args){
            Isolate* isolate = args.GetIsolate();

            // Create a new global fs object
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
            FSObject->Set(String::NewFromUtf8(isolate, "db"), File_DB());

            // Return the newly created FS object
            args.GetReturnValue().Set(FSObject);
            return 1;
        }

        /*
        * Mask Function called within the object. 
        * Calls: fs.exists(path)
        * returns boolean
        */
        void FileExists(const FunctionCallbackInfo<Value>& args){           
            if (args.Length() != 1 || !args[0]->IsString())
                THROW( "Invalid Arguments");

            else{
                Local<Value> val = args[0];
                std::string filename(TO_STRING(val));
                args.GetReturnValue().Set(Boolean::New(args.GetIsolate(), FileExists(filename)));
            } 
        }

        /*
        * Finds if the file exists or not
        */
        bool FileExists(std::string filename){
            struct stat buf;
            return stat(filename.c_str(), &buf) != -1;
        }

        /*
        * Function called within the object to return the stats of the file
        * Calls: fs.fileInfo(path)
        */
        void FileInfo(const FunctionCallbackInfo<Value>& args){
            if (args.Length() != 1 || !args[0]->IsString())
                THROW( "Invalid Arguments");

            else{
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
        }

        /*
        * Opens and returns the contents of the file as a string
        * Calls: fs.open(path);
        */
        void Open(const FunctionCallbackInfo<Value>& args){
            if (args.Length() < 1 || !args[0]->IsString())
                THROW( "Invalid Arguments");

            else{
                Local<Value> val = args[0];
                const char* strVal = TO_STRING(val);

                // Check if file exists
                if (!FileExists(strVal))
                    THROW( "File doesn't exist");
                std::string filename(strVal);

                // Read the file to a v8 string
                Handle<String> contents = ReadFile(args.GetIsolate(), TO_CHAR(filename));
                if (contents->Length() < 1)
                    THROW( "Empty File");
                args.GetReturnValue().Set(contents);
            }
        }

        /*
        * Deletes a file. Returns true if successful, returns false if not
        * calls: fs.deleteFile(path)
        */
        void DeleteFile(const FunctionCallbackInfo<Value>& args){
            if (args.Length() < 1 || !args[0]->IsString())
                THROW( "Invalid Arguments");

            else{
                Local<Value> val = args[0];
                std::string filename(TO_STRING(val));
                bool removed = false;

                if (remove(TO_CHAR(filename)) == 0){
                    removed = true;
                }

                args.GetReturnValue().Set(Boolean::New(args.GetIsolate(), removed));
            }
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
                THROW( "Invalid Arguments");

            else{
                Local<Value> val = args[0];
                std::string filename(TO_STRING(val));
                DIR *dir;
                struct dirent *ent;
                bool more = false;
                if (args.Length() > 1 && args[1]->IsBoolean())
                    more = args[1]->ToBoolean()->Value();

                if ((dir = opendir (TO_CHAR(filename))) != NULL) {
                /* print all the files and directories within directory */
                    Local<Array> dirObj = Array::New(args.GetIsolate());
                    int i = 0;
                    while ((ent = readdir (dir)) != NULL) {
                        if (more){
                            Local<Object> fileObj = Object::New(args.GetIsolate());
                            fileObj->Set(String::NewFromUtf8(args.GetIsolate(), "size"), Number::New(args.GetIsolate(), ent->d_reclen));
                            fileObj->Set(String::NewFromUtf8(args.GetIsolate(), "name"), String::NewFromUtf8(args.GetIsolate(), ent->d_name));
                            dirObj->Set(Number::New(args.GetIsolate(), i++), fileObj);
                        }
                        else
                            dirObj->Set(Number::New(args.GetIsolate(), i++), String::NewFromUtf8(args.GetIsolate(), ent->d_name));
                    }
                    closedir (dir);

                    // Return value
                    args.GetReturnValue().Set(dirObj);
                } 
                else {
                    /* could not open directory */
                    THROW( "Unable to open dir");
                }
            }
        }

        void Write(const FunctionCallbackInfo<Value>& args){
            if (args.Length() < 2 || !args[0]->IsString())
                THROW( "Invalid Arguments");

            else{
                Local<Value> val = args[0];
                std::string filename(TO_STRING(val));
                Local<Value> contents = args[1];
                std::string str(TO_STRING(contents));
                std::ofstream file(TO_CHAR(filename));
                file.open(TO_CHAR(filename));
                file << str;
                file.close();
                args.GetReturnValue().Set(Boolean::New(args.GetIsolate(), true));
            }
        }

        void Rename(const FunctionCallbackInfo<Value>& args){
            if (args.Length() < 2 || !args[0]->IsString() || !args[1]->IsString())
                THROW( "Invalid Arguments");

            else{
                Local<Value> old = args[0];
                std::string oldname(TO_STRING(old));
                Local<Value> n = args[1];
                std::string newname(TO_STRING(n));

                int success = rename(TO_CHAR(oldname), TO_CHAR(newname));
                if (success == 0)
                    args.GetReturnValue().Set(Boolean::New(args.GetIsolate(), success == 0));
                else
                    THROW( &"Error code: " [success]);  
            }   
        }


        // DB object
        Handle<Object> File_DB(){
            Isolate* isolate = Isolate::GetCurrent();
            Handle<Object> dbObj = Object::New(isolate);
            dbObj->Set(String::NewFromUtf8(isolate, "save"), Function::New(isolate, DBSave));
            return dbObj;
        }

        void DBSave(const FunctionCallbackInfo<Value>& args){
            if (args.Length() < 2 || !args[0]->IsString() || !args[1]->IsString())
                THROW( "Invalid arguments");
            else{
                THROW( "Under Construction");
            }
        }
    }
}