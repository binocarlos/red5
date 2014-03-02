#!/usr/bin/env node
var argv = require('optimist').argv;
var fs = require('fs');
var child = require('child_process');

var input_file = fs.createReadStream('./input.ts');
var output_file = fs.createWriteStream('./output.mp4');

var args = ['-i', 'pipe:0', '-f', 'mp4', '-movflags', 'frag_keyframe', 'pipe:1'];
var trans_proc = child.spawn('avconv', args, null);

input_file.pipe(trans_proc.stdin);
trans_proc.stdout.pipe(output_file);

trans_proc.stderr.on('data', function (data) {
    console.log(data.toString());
});