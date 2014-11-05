#!/usr/bin/env python
#  Copyright Chase Willden and the JSK Authors.
# 
#  Permission is hereby granted, free of charge, to any person obtaining a
#  copy of this software and associated documentation files (the
#  "Software"), to deal in the Software without restriction, including
#  without limitation the rights to use, copy, modify, merge, publish,
#  distribute, sublicense, and/or sell copies of the Software, and to permit
#  persons to whom the Software is furnished to do so, subject to the
#  following conditions:
# 
#  The above copyright notice and this permission notice shall be included
#  in all copies or substantial portions of the Software.
# 
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
#  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
#  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
#  NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
#  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
#  OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
#  USE OR OTHER DEALINGS IN THE SOFTWARE.
import os
import sys
import platform

def get_ccs():
  return [
    'src/include/include.cc',
    'src/api/os/os.cc',
    'src/api/fs/fs.cc',
    'src/api/http/http.cc',
    'src/common/format/format.cc',
    'src/api/shell/shell.cc',
    'src/common/globals/globals.cc',
    'src/api/socket/socket.cc',
    'src/common/env.cc',
    'src/api/window/window.cc',
    'src/api/window/window.mm'
  ]

def get_objc():
  return [
    'src/api/window/window.mm'
  ]

def main():
  if (len(sys.argv) < 2):
    print('Missing argument type: v8|build|run')
    return
  build_type = sys.argv[1]
  if (build_type == 'v8'):
    make_type = sys.argv[2]
    print("Building V8 engine...")
    os.system('cd deps/v8')
    os.system('make -C deps/v8 ' + make_type)
  if (build_type == 'build'):
    print("Pulling in resources...AKA, all of the JS files")
    os.system('tools/js2c.py src/js_natives.h src/resources/resources.jsk');
    print("Completed")
    print("Building System")
    pre = 'clang++ -lcurl -Iinclude deps/v8/out/native/libv8_base.a deps/v8/out/native/libv8_libbase.a deps/v8/out/native/libv8_snapshot.a deps/v8/out/native/libicudata.a deps/v8/out/native/libicuuc.a deps/v8/out/native/libicui18n.a'
    middle = ''
    ccs = get_ccs()
    for i in ccs:
      middle += ' ' + i
    build_arch = sys.argv[2]
    if (build_arch == 'darwin'):
      objc = get_objc()
      middle += ' -ObjC++'
      for i in objc:
        middle += ' ' + i

    post = ' src/main.cc -o build/jsk -stdlib=libstdc++'
    os.system(pre + middle + post)
    print("Completed")
  if (build_type == 'run'):
    print("Running Shoelace...")
    if (len(sys.argv) > 2):
      os.system("build/jsk " + sys.argv[2])
    else:
      os.system("build/jsk")
    

if __name__ == "__main__":
  main()