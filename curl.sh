#!/bin/bash

pushd $PWD/curl-7.65.2
    ./configure --prefix=$PWD/install --enable-shared=no
    make
    make install
popd
