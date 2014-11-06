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

function menuBuilder(masterClass){
	if (!masterClass)
		throw new String('Invalid class name');
	this.items = [];
	include('documentBuilder');
	var builder = include('documentBuilder');
	this.ele = new builder('ul');
	this.ele.addClass(masterClass);
	this.masterClass = masterClass;
}

menuBuilder.prototype.addItem = function(options){
	if (!options)
		throw new String('Invalid options');
	include('documentBuilder');
	var builder = include('documentBuilder');
	var item = new builder('li');
	if (options.className)
		item.addClass(options.className);
	if (options.text)
		item.text(options.text);
	item.addClass('menu-item');
	item.attr('id', 'menu-item-' + this.items.length);
	this.ele.append(item);
	this.items.push(item);
}

menuBuilder.prototype.getStyle = function(type){
	var styles = {
		dropdown: "." + this.masterClass + "{position:absolute;width:210px;margin:0;padding:0;box-shadow:0 0 18px -2px rgba(0,0,0,.7);z-index:9999}." + this.masterClass + " .menu-item{padding: 5px 15px;border-left:solid 4px transparent}." + this.masterClass + " .menu-item:hover{border-left-color:rgb(131, 131, 131);background-color:rgb(224, 224, 224);cursor:pointer;}"
	}
	if (styles[type])
		return styles[type];
	return styles.dropdown;
}

menuBuilder.prototype.build = function(){
	return this.ele.build();
}