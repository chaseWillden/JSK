CC=g++
TGT=build
INCLUDES = -Iinclude $(wildcard deps/v8/out/native/*.a)
FLAGS = -Wall -stdlib=libstdc++ -std=c++11 $(INCLUDES)

CC_FILES = $(shell find src -type f -name "*.cc" ! -name "main.cc")

all: JS buildCC

JS:
	tools/js2c.py src/js_natives.h src/resources/nativeJs.jsk

buildCC: 
	$(CC) $(FLAGS) $(CC_FILES) src/main.cc -o build/jsk 

v8:
	make -C deps/v8

run:
	./build/jsk

test2:
	./build/jsk test/fs.js

clean:
	rm -rf build/*.o