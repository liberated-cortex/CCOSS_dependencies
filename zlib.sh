#!/bin/bash
source dirs.sh

pushd $ZLIB_DIR
    ./configure --static --prefix=$PWD/install
    make
    make install
popd
