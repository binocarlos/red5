#!/usr/bin/env node

var raspivid = require('raspivid');
var tee = require('tee');
var transcoder = require('./transcoder');
var fs = require('fs');

module.exports = function(options){
	
	var hdfile = fs.createWriteStream('/home/pi/hd.h264');
	var smallfile = fs.createWriteStream('/home/pi/small.h264');

	var smalltranscode = transcoder({
		width:640,
		height:480
	})

	var video = raspivid({
		
	});

	video.stdout.on('end', function(){
		console.log('-------------------------------------------');
		console.log('video done');
	})

	
	//video.stdout.pipe(smalltranscode.stdin);
	video.stdout.pipe(hdfile);
	video.stdout.pipe(smallfile);
	//smalltranscode.stdout.pipe(smallfile);

	
	/*

	smalltranscode.stdout.pipe(smallfile);
	video.stdout.pipe(smalltranscode.stdin);







	tee(
		hdfile,
		smalltranscode.stdin
	))

	smalltranscode.stdout.pipe(smallfile);
	


	smalltranscode.on('data', function(d){
		console.log('d: ' + d.length);
	})	*/
}