#!/bin/bash
source dirs.sh

pushd $BSD_DIR
    ./configure --prefix=$PWD/install --enable-shared=no
    make
    make install
popd
