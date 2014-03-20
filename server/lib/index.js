#!/usr/bin/env node
var argv = require('optimist').argv;
var http = require('http');
var WebSocketServer = require('ws').Server;
var express = require('express');
var ecstatic = require('ecstatic');

var app = express();
var server = http.createServer(app);
var socketserver = new WebSocketServer({server: server});

app.get('/test', function(req, res){

})

wss.on('connection', function(ws) {
  ws.on('message', function(message) {
    console.log('received: %s', message);
  });
  ws.send('something');
});

server.listen(80, function(){
	console.log('server listening on port 80');
})