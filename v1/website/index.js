#!/usr/bin/env node

var express = require('express');
var http = require('http');
var socketio = require('socket.io');
var _ = require('lodash');
var fs = require('fs');

var document_root = __dirname + '/www'
var port = 80;

var app = express();
var server = http.createServer(app);

app.use(express.query());
app.use(express.bodyParser());

var io = socketio.listen(server);

if(process.env.NODE_ENV=='production'){
  io.enable('browser client minification');
  io.enable('browser client etag');
  io.enable('browser client gzip');
}

io.set('log level', 1);
io.set('transports', [
    'websocket'
  , 'flashsocket'
  , 'htmlfile'
  , 'xhr-polling'
  , 'jsonp-polling'
])

app.use(express.static(document_root));

var counter = 0;

app.post('/ping', function(req, res){
  try{
    var packet = req.body;

    io.sockets.emit('packet', packet);

    res.send('ok');

    fs.appendFile(__dirname + '/alldata.txt', JSON.stringify(packet) + "\n", function(){

    })  
  }
  catch (e){

  }
  
})

io.sockets.on('connection', function(socket){

  console.log('-------------------------------------------');
  console.log('socket connection');
/*
  socket.on('move:request', function(packet){

    console.log('-------------------------------------------');
    console.log('move gotten');
    console.dir(packet);

    socket.emit('move:response', {
      id:packet.id,
      title:packet.title,
      counter:counter++
    })

  })
*/  
})

server.listen(port, function(){
  console.log('-------------------------------------------');
  console.log('document_root: ' + document_root);
  console.log('port: ' + port);
})