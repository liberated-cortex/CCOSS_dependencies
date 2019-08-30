#!/bin/bash
source dirs.sh

pushd $PNG_DIR
    ./configure --prefix=$PWD/install --enable-shared=no --with-sysroot=$ZLIB_DIR/install
    make
    make install
popd
