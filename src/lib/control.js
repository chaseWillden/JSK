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

var control = {
	start: function(port){
		var http = include('http');
		var server = http.createServer(function(res, req){
			res.start();
			res.write("<h1>Todos</h1><ul><li>Allow to request other pages (i.e. stylesheets)</li><li>Call the create server function each GET request</li></ul>");
			if (req){
				for (r in req){
					res.write(r.toString() + ' ' + req[r].toString());
				}
			}
		});
		var port = port ? port : 4001;
		server.listen(port, "Listening on port " + port);
	}
}