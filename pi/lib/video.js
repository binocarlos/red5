#!/usr/bin/env node

var Raspivid = require('raspivid');
var through = require('through');
var fs = require('fs');

module.exports = function(options){
	
	options = options || {};
	var sessionfile = options.filepath;

	var count = 0;
	var framecounter = through(function write(data) {
		count++;
    this.queue(data)
  },
  function end () {
  	console.log('-------------------------------------------');
  	console.log('stream ended');
    this.queue(null)
  })

	var video = Raspivid({
		width:options.width,
		height:options.height
	});

	video.on('end', function(){
		console.log('-------------------------------------------');
		console.log('video done');
	})

	video.pipe(sessionfile);
	video.pipe(framecounter);
}