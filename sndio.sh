#!/bin/bash

pushd $PWD/sndio-1.6.0
    ./configure --prefix=$PWD/install
    make
    make install
    cd $PWD/libsndio
    ar rcs libsndio.a *.o
popd
