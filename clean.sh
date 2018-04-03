#!/bin/sh

# clean FileMgrComp
cd FileMgrComp
make clean

# clean TextSearchComp
cd ../TextSearchComp
make clean

# clean client
cd ../Client
make clean

cd ..



