var print = include('print');
var fs = include('fs');

print("Testing fs...");

var inDirTrue = fs.inDir('test/fs/fsmain.js');
var inDirFalse = fs.inDir('test/fs/fsmain2.js');

print('fs.inDir - true: ' + inDirTrue);
print('fs.inDir - false: ' + inDirFalse);