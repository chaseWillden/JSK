var fs = include('fs');

print("Testing FS module", false);
print("=================\n\n", false);

// Test write function
var writeData = 'This is a test';
var written = fs.write('test/writeTest.txt', writeData);
print("Testing fs.write..." + (written ? "done" : "failed"), false);

// Test exists function
var exists = fs.exists('test/fs.js');
print("Testing fs.exists..." + (exists ? "done" : "failed"), false);

// Test open function
var openData = fs.open('test/writeTest.txt');
if (openData == "This is a test")
	print("Testing fs.open...Done", false);
else
	print("Testing fs.open...failed", false);

var fileInfo = fs.fileInfo('test/writeTest.txt');
if (typeof fileInfo == 'object')
	print("Testing fs.fileInfo...done", false);
else
	print("Testing fs.fileInfo...failed", false);

var readDir = fs.readDir('test');
if (readDir.length > 2)
	print("Testing fs.readDir...done", false);
else
	print("Testing fs.readDir...failed", false);

var inDir = fs.inDir('test', 'writeTest.txt');
print("Testing fs.inDir..." + (inDir ? "done" : "failed"), false);

var isDir = fs.isDir('test');
var isDir2 = fs.isDir('test/writeTest.txt');
print("Testing fs.isDir..." + ((isDir && !isDir2) ? "done" : "failed"), false);

fs.rename("test/writeTest.txt", "test/writeTestNew.txt");
var existsTwo = fs.exists("test/writeTestNew.txt");
fs.rename("test/writeTestNew.txt", "test/writeTest.txt");
print("Testing fs.rename..." + (existsTwo ? "done" : "failed"), false);

fs.deleteFile('test/writeTest.txt');
if (fs.exists('test/writeTest.txt'))
	print("Testing fs.delete...failed", false);
else
	print("Testing fs.delete...done", false);

print("Done testing FS module", false);
