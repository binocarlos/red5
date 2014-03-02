#!/usr/bin/env node
var argv = require('optimist').argv;

var http = require('http');
var express = require('express');

var app = express();
var server = http.createServer(app);



server.listen(80, function(){
	console.log('server listening on port 80');
})