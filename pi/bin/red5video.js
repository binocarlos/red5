#!/usr/bin/env node
var argv = require('optimist').argv;
var Video = require('../lib/video');

Video({
	width:argv.width || 800,
	height:argv.height || 600,
	filepath:argv.filepath || '/tmp/red5video.h264',
	sessionid:argv.sessionid || 'session'
});
