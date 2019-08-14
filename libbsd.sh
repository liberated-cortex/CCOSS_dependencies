#!/bin/bash

pushd $PWD/libbsd-0.10.0
    ./configure --prefix=$PWD/install --enable-shared=no
    make
    make install
popd
