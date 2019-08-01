#!/bin/bash

pushd $PWD/libogg-1.3.3
    ./autogen.sh
    ./configure --prefix=$PWD/install --enable-shared=no
    make
    make install
popd
