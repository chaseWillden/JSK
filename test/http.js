var h = include('http');
var s = h.createServer(function(res, req){
	res.write('<h1>Test</h1>');
});
s.listen(4000);