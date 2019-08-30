#!/bin/bash
source dirs.sh

pushd $ALLEGRO_DIR
    mkdir build
    cd build
    cmake -DCMAKE_INSTALL_PREFIX=$PWD/../install -DSHARED=NO ../
    make
    make install
popd
