#!/bin/bash

pushd $PWD/libbsd-0.9.1
    ./configure --prefix=$PWD/install --enable-shared=no
    make
    make install
popd
