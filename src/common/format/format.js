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

// Colors: http://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
// Colors: http://en.wikipedia.org/wiki/ANSI_escape_code

var format = {
	console: function(obj){
		var type = this.getType(obj);
		var noExpand = '[String]|[Number][Boolean]';
		if (type.indexOf('Object') != -1 || type.indexOf('Array') != -1)
			return this.loopThroughObj(obj);
		else if (type.indexOf('Function') != -1)
			return this.setColor(type) + ' ' + this.displayParams(obj);
		else if (noExpand.indexOf(type) != -1)
			return obj + ' ' + this.setColor(type);
		else
			return this.setColor(type, true);
	},
	loopThroughObj: function(obj){
		var results;
		if (this.getType(obj).indexOf('Array') != -1)
			results = '\n  [\n';
		else if (this.getType(obj).indexOf('Object') != -1)
			results = '\n  {\n';
		var type = '';
		var noExpand = '[String]|[Number]|[Boolean]';
		for (item in obj){
			type = this.getType(obj[item]);
			results += '   - '; 
			if (noExpand.indexOf(type) != -1)
				results += this.setColor(item, true) + ': ' + obj[item];
			else if (type === '[Function]'){
				results += item + ': ' + this.setColor(type) + ' ' + this.displayParams(obj[item]);
			}
			else
				results += item + ': ' + this.setColor(type);
			results += '\n';
		}
		if (this.getType(obj).indexOf('Array') != -1)
			return results + '  ]\n';
		else if (this.getType(obj).indexOf('Object') != -1)
			return results + '  }\n';
	},
	displayParams: function(func){
		var results;
		results = '( ';
		var params = this.getParamNames(func);
		for (var i = 0; i < params.length; i++)
			if (i == params.length - 1)
				results += params[i];
			else
				results += params[i] + ', ';
		return results + ' )';
	},
	getType: function(obj){
		var type = Object.prototype.toString.call(obj);
		return type.replace('object ', '');
	},
	setColor: function(type, override){
		var codes = {
			ESCAPE: '\033',
			BOLD: '[1;',
			NORMAL: '[0;',
			RED: '31m',
			GREEN: '32m',
			YELLOW: '33m',
			BLUE: '34m',
			MAGENTA: '35m',
			GYAN: '36m',
			NONE: '[0m'
		};
		var color;
		if (override)
			color = codes.GYAN;
		else if (type.indexOf('String') > 0)
			color = codes.GREEN;
		else if (type.indexOf('Boolean') > 0)
			color = codes.BLUE;
		else if (type.indexOf('Array') > 0)
			color = codes.YELLOW;
		else if (type.indexOf('Function') > 0)
			color = codes.BLUE;
		else if (type.indexOf('Number') > 0)
			color = codes.RED;
		else if (type.indexOf('Object') > 0)
			color = codes.MAGENTA;
		else if (type.indexOf('[RegExp]') > 0)
			color = color.GREEN;
		else
			color = codes.NORMAL;
		return codes.ESCAPE + codes.NORMAL + color + type + codes.ESCAPE + codes.NONE;
	},
	STRIP_COMMENTS: /((\/\/.*$)|(\/\*[\s\S]*?\*\/))/mg,
	ARGUMENT_NAMES: /([^\s,]+)/g,
	getParamNames: function(func) {
		var fnStr = func.toString().replace(this.STRIP_COMMENTS, '')
		var result = fnStr.slice(fnStr.indexOf('(')+1, fnStr.indexOf(')')).match(this.ARGUMENT_NAMES)
		if(result === null)
	    	result = []
	  	if (fnStr.indexOf('native code') != -1)
	  		result = ['[native code]'];
	 	return result
	}
}