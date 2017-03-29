#!/bin/bash

port="$(lsof -i | grep 12345 | awk '{ print $2 }')"
kill -9 $port
