#!/bin/bash

if [ -n $1 ] && [ "$1" = "debug" ]; then
  echo "--------------------------"
  echo "Execute cmake in debug mode"
  echo "--------------------------"
  cmake -DCMAKE_BUILD_TYPE=Debug . -G"Unix Makefiles"
else
  echo "--------------------------"
  echo "Execute cmake in release mode"
  echo "--------------------------"
  cmake -DCMAKE_BUILD_TYPE=Release . -G"Unix Makefiles"
fi 
