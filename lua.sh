#!/bin/bash
source dirs.sh

pushd $LUA_DIR
    make linux
    make install
popd
