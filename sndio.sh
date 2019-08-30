#!/bin/bash
source dirs.sh

pushd $SNDIO_DIR
    ./configure --prefix=$PWD/install
    make
    make install
    cd $PWD/libsndio
    ar rcs libsndio.a *.o
popd
