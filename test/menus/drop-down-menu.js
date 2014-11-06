include('menuBuilder');
var builder = include('menuBuilder');
var menu = new builder('top-menu');
menu.addItem({
	text: 'Save'
});
menu.addItem({
	text: 'print'
});
menu.addItem({
	text: 'Export'
});
menu.addItem({
	text: 'Return'
});
var html = menu.build();
var style = menu.getStyle();

var http = include('http');
var server = http.createServer(function(res, req){
	res.start();
	if (req.GET && req.GET === '/'){
		res.write('<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><title>Document</title><link rel="stylesheet" type="text/css" href="style.css"></head><body>' + html + '</body></html>');
	}
	else if (req.GET && req.GET === '/style.css'){
		res.write(style);
	}
	print(req);
});
server.listen(4000);