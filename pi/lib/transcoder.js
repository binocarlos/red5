#!/usr/bin/env node
var child = require('child_process');

module.exports = function(options){
	options = options || {};
	var size = options.size || '640x480';

	if(options.width && options.height){
		size = options.width + 'x' + options.height;
	}

	// avconv to convert video down a size
	var args = ['-i', 'pipe:0', '-s', size, 'pipe:1'];

	// the avconv stream that inherits stderr
	return child.spawn('avconv', args, {
		stdio: 'pipe'
	});
}