// Copyright 2012 the V8 project authors. All rights reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
//       copyright notice, this list of conditions and the following
//       disclaimer in the documentation and/or other materials provided
//       with the distribution.
//     * Neither the name of Google Inc. nor the names of its
//       contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "../deps/v8/include/v8.h"
#include "common/macros.h"
#include "include/include.h"
#include "common/globals/globals.h"
#include "common/env.h"

#include <stdio.h>
#include <string.h>

using namespace v8;

#ifdef COMPRESS_STARTUP_DATA_BZ2
#error Using compressed startup data is not supported for this sample
#endif

/**
 * This sample program shows how to implement a simple javascript shell
 * based on V8.  This includes initializing V8 with command line options,
 * creating global functions, compiling and executing strings.
 *
 * For a more sophisticated shell, consider using the debug shell D8.
 */

void RunShell(Handle<Context> context);
int RunMain(Isolate* isolate, int argc, char* argv[]);
Handle<String> ReadFile(Isolate* isolate, const char* name);

Handle<ObjectTemplate> global_;
static JSK::Env env;

static bool run_shell;

int main(int argc, char* argv[]) {
  Isolate* isolate = env.Init(argc, argv);
  run_shell = (argc == 1 || argc == 2);
  int result;
  {
    Isolate::Scope isolate_scope(isolate);
    HandleScope handle_scope(isolate);
    Handle<Context> context = env.CreateGlobals();
    if (context.IsEmpty()) {
      fprintf(stderr, "Error creating context\n");
      return 1;
    }
    Context::Scope context_scope(context);
    result = RunMain(isolate, argc, argv);
    if (run_shell) RunShell(context);
  }
  V8::Dispose();
  return result;
}

// Process remaining command line arguments and execute files
int RunMain(Isolate* isolate, int argc, char* argv[]) {
  for (int i = 1; i < argc; i++) {
    const char* str = argv[i];
    if (strcmp(str, "--shell") == 0) {
      run_shell = true;
    } else if (strcmp(str, "-f") == 0) {
      // Ignore any -f flags for compatibility with the other stand-
      // alone JavaScript engines.
      continue;
    } else if (strncmp(str, "--", 2) == 0) {
      fprintf(stderr,
              "Warning: unknown flag %s.\nTry --help for options\n", str);
    } else if (strcmp(str, "-e") == 0 && i + 1 < argc) {
      // Execute argument given to -e option directly.
      Handle<String> file_name =
          String::NewFromUtf8(isolate, "unnamed");
      Handle<String> source =
          String::NewFromUtf8(isolate, argv[++i]);
      if (!env.Execute(true, source, file_name)) return 1;
    } else {
      // Use all other arguments as names of files to load and run.
      Handle<String> file_name = String::NewFromUtf8(isolate, str);
      Handle<String> source = ReadFile(isolate, str);
      if (source.IsEmpty()) {
        fprintf(stderr, "Error reading '%s'\n", str);
        continue;
      }
      Local<Value> strt = source;
      if (!env.Execute(true, source, file_name)) return 1;
    }
  }
  return 0;
}

// Reads a file into a v8 string.
Handle<String> ReadFile(Isolate* isolate, const char* name) {
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
  Handle<String> result =
      String::NewFromUtf8(isolate, chars, String::kNormalString, size);
  delete[] chars;
  return result;
}


// The read-eval-execute loop of the shell.
void RunShell(Handle<Context> context) {
  fprintf(stderr, "Welcome to Shoelace\n");
  static const int kBufferSize = 256;
  // Enter the execution environment before evaluating any code.
  Context::Scope context_scope(context);
  Local<String> name(
      String::NewFromUtf8(context->GetIsolate(), "(shell)"));
  while (true) {
    char buffer[kBufferSize];
    fprintf(stderr, "> ");
    char* str = fgets(buffer, kBufferSize, stdin);
    if (str == NULL) break;
    HandleScope handle_scope(context->GetIsolate());
    env.Execute(true,
                  String::NewFromUtf8(context->GetIsolate(), str),
                  name);
  }
  fprintf(stderr, "\n");
}
