#!/bin/bash

pushd $PWD/SDL2-2.0.9
    ./configure --prefix=$PWD/install --enable-shared=no --disable-alsatest --disable-esdtest
    make
    make install
popd
