#!/bin/bash
source dirs.sh

pushd $MINIZIP_DIR
    mkdir build
    cd build
    cmake -DCMAKE_INSTALL_PREFIX=$PWD/../install ../
    make
    make install
popd
