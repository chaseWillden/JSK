JSK
===
Another alternative to Node.js. Another purpose to this is to include native OS GUI api's.

Supported Features
===================
```
fs = {
	inDir: function(dir, filePath){},
	isDir: function(path),
	deleteDir: function(path),
	exists: function(filePath),
	open: function(filePath),
	fileInfo: function(filePath),
	deleteFile: function(filePath),
	readDir: function(dir),
	write: function(filePath, data),
	rename: function(oldFilePath, newFilePath)
}

os = {
	launch: function(programName),
	platform: [String],
	cpus: [Number],
	hostname: [String]
}

shell = {
	execute: function(command),
	print: function(obj)
}

http = {
	createServer: function(response, request) // Very buggy right now
}

var Doc = include('documentBuilder');
var d = new Doc(tagName);
d.attr(name, value);
d.append(ele);
d.prepend(ele);
d.text(txt);
d.addClass(name);
var htmlString = d.build();
```

Build
=====

The current solution is build specifically for Mac, I'll work on Windows in a little while

Required
--------
Clang++
Python

Build V8
--------
Go to JSK base directory
    ./jsk.py v8 [native or just leave blank for all]

Build JSK
----------
Go to JSK base directory
    ./jsk.py build

Run
----
Go to JSK base directory
    ./jsk.py run
	./jsk.py run [filename]


Todos:
------
fs.deleteDir
