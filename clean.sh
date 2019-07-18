#!/bin/bash
ZLIB_DIR=$PWD/zlib-1.2.11
PNG_DIR=$PWD/libpng-1.6.37
OGG_DIR=$PWD/libogg-1.3.3
VORBIS_DIR=$PWD/libvorbis-1.3.6
SDL_DIR=$PWD/SDL2-2.0.9
SDL_MIXER_DIR=$PWD/SDL2_mixer-2.0.4
SNDIO_DIR=$PWD/sndio-1.5.0/libsndio
ALLEGRO_DIR=$PWD/allegro5-4.4.3.1
LUA_DIR=$PWD/lua-5.1.5
MINIZIP_DIR=$PWD/minizip-1.2
CURL_DIR=$PWD/curl-7.65.2

rm -r prepared

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
pushd $SDL_DIR
    make clean
    rm -r install/
popd
pushd $SDL_MIXER_DIR
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
pushd $CURL_DIR
    rm -r build/
    rm -r install/
popd
