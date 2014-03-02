#!/bin/sh
 
VERSION=0.11.0
PLATFORM=linux
ARCH=arm-pi
NODE="node-v$VERSION-$PLATFORM-$ARCH"

mkdir -p "/tmp/nodeversions/$VERSION"

curl http://nodejs.org/dist/v$VERSION/$NODE.tar.gz \
  | tar xzvf - --strip-components=1 -C "/tmp/nodeversions/$VERSION"
#export PATH=$PATH:$PREFIX/node-v$VERSION-$PLATFORM-$ARCH/bin