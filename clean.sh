#!/bin/bash
ZLIB_DIR=$PWD/zlib-1.2.11
PNG_DIR=$PWD/libpng-1.6.37
OGG_DIR=$PWD/libogg-1.3.3
VORBIS_DIR=$PWD/libvorbis-1.3.6
SNDIO_DIR=$PWD/sndio-1.6.0/libsndio
ALLEGRO_DIR=$PWD/allegro5-4.4.3.1
LUA_DIR=$PWD/lua-5.1.5
MINIZIP_DIR=$PWD/minizip-1.2
BSD_DIR=$PWD/libbsd-0.9.1
GORILLA_AUDIO_DIR=$PWD/GorillaAudio

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
