#!/bin/bash
source dirs.sh

pushd $OGG_DIR
    ./autogen.sh
    ./configure --prefix=$PWD/install --enable-shared=no
    make
    make install
popd
