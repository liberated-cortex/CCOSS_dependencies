#!/bin/bash
source dirs.sh

rm -r prepared

pushd $GORILLA_AUDIO_DIR
    rm -r build/build
popd
pushd $BSD_DIR
    make clean
    rm -r install/
popd
pushd $ZLIB_DIR
    make clean
    rm -r install/
popd
pushd $PNG_DIR
    make clean
    rm -r install/
popd
pushd $OGG_DIR
    make clean
    rm -r install/
popd
pushd $VORBIS_DIR
    make clean
    rm -r install/
popd
pushd $SNDIO_DIR
    make clean
    rm -r install/
popd
pushd $ALLEGRO_DIR
    rm -r build/
    rm -r install/
popd
pushd $LUA_DIR
    make clean
    rm -r install/
popd
pushd $MINIZIP_DIR
    rm -r build/
    rm -r install/
popd
