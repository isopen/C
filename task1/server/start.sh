#!/bin/bash

make -j 6
if [ -n $1 ]
then
  ./build/release/dec $1
else
  ./build/release/dec
fi
