#!/bin/sh

# compile FileMgrComp
cd FileMgrComp
make

# compile TextSearchComp
cd ../SearchComp
make

# compile client
cd ../Client
make

cd ..


