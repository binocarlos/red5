#!/usr/bin/env bash

VERSION=0.11.0
PLATFORM=linux
ARCH=arm-pi
PREFIX="/usr/local"
 
mkdir -p "$PREFIX" && \
curl http://nodejs.org/dist/v$VERSION/node-v$VERSION-$PLATFORM-$ARCH.tar.gz \
  | tar xzvf - --strip-components=1 -C "$PREFIX"