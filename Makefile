CC=g++
TGT=build
INCLUDES = -Iinclude $(wildcard deps/v8/out/native/*.a)
FLAGS = -Wall -stdlib=libstdc++ -std=c++11 $(INCLUDES)

CC_FILES = $(shell find src -type f -name "*.cc" ! -name "main.cc")

buildCC: 
	$(CC) $(FLAGS) $(CC_FILES) src/main.cc -o build/jsk 

buildjs:
	tools/js2c.py src/js_natives.h src/resources/nativeJs.jsk

v8:
	make -C deps/v8

run:
	./build/jsk

clean:
	rm -rf build/*.o

all:
	buildjs buildCC