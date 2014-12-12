// Copyright Chase Willden (chase.willden@gmail.com) and other Cobra contributors.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to permit
// persons to whom the Software  is furnished to do so, subject to the
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

var fs = {
	inDir: function(dir, file){
		if (!file)
			throw new String("Invalid arguments");
		var contents = fs.readDir(dir);
		var len = contents.length;
		while(len--){
			if (contents[len] == file)
				return true;
		}
		return false;
	},
	isDir: function(path){
		var info = fs.fileInfo(path);
		return info.isDir;
	},
	deleteDir: function(path){
		if (!fs.isDir(path))
			throw new String('Invalid directory');
		var path = path[path.length - 1] == '/' ? path : path + '/';
		var contents = fs.readDir(path);
		var len = contents.length;
		while(len--){
			if (fs.isDir(contents[len])){
				// Clear call stack
				setTimeout(function(){
					fs.deleteDir(contents[len]);
				}, 1);
			}
			else{
				if (fs.deleteFile(path + contents[len]))
					success++;
			}
		}
	},
	gui: function(current){
		var os = include('os');
		if (os.platform == 'Apple')
			if (current)
				os.launch('.');
			else
				os.launch('Finder');
		else if (os.platform == 'Windows')
			if (current)
				os.launch('.');
			else
				os.launch('Explorer');
	},
	exists: function(path){
		if (!path)
			throw new String('Invalid path');
		var filename;
		var contents;
		var split;

		var os = include('os');
		if (os.platform == "Windows"){
			split = path.split('\\');
		}
		else{
			split = path.split('/');
		}

		if (split.length > 1){
			filename = split[split.length - 1];
			var stitch = '';
			for (var i = 0; i < split.length; i++){
				if (i < split.length - 1)
					stitch += split[i];
			}
			contents = fs.readDir(stitch);
		}
		else{
			filename = path
			contents = fs.readDir("./");
		}

		for (var i = 0; i < contents.length; i++){
			if (contents[i] == filename)
				return true;
		}
		return false;
	}
}