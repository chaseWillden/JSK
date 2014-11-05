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

function documentBuilder(tagName){
	this.tagName = tagName;
	this.attributes = {};
	this.children = [];
	this.parent;
	this.classNames = {};
	this.txt;
}

documentBuilder.prototype.attr = function(name, value){
	if (!name)
		throw new String('Invalid arguments');
	else if (!value)
		return this.attributes[name];
	this.attributes[name] = value;
}

documentBuilder.prototype.append = function(ele){
	if (!ele)
		throw new String('Invalid arguments');
	ele.parent = this;
	this.children.push(ele);
}

documentBuilder.prototype.prepend = function(ele){
	if (!ele)
		throw new String('Invalid arguments');
	ele.parent = this;
	this.children.unshift(ele);
}

documentBuilder.prototype.text = function(txt){
	this.txt = txt;
}

documentBuilder.prototype.addClass = function(name){
	if (!name)
		throw new String('Invalid arguments');
	this.classNames[name] = '';
}

documentBuilder.prototype.build = function(){
	var result = '<' + this.tagName;
	var attr;
	var className;
	for (attr in this.attributes){
		result += ' ' + attr + "'" + this.attributes[attr] + "'";
	}

	result += ' class=\'';
	for (className in this.classNames){
		result += ' ' + className;
	}
	result += '\'';
	result += ">" + this.text + "</" + this.tagName + ">";
	return result;
}