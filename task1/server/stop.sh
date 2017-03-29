#!/bin/bash

pid="$(lsof -i | grep 12345 | awk '{ print $2 }')"
kill -9 $pid
