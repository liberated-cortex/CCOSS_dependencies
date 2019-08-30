#!/bin/bash
source dirs.sh

pushd $VORBIS_DIR
    export CFLAGS="-g"
    ./configure --prefix=$PWD/install --enable-shared=no --with-ogg=$OGG_DIR/install
    make
    make install
popd
