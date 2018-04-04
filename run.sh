#!/bin/sh

cd Client
dist/Debug/GNU-Linux/client "(.*?)long(.*?)" "." "*.txt" "*.cpp" "*.h" 
