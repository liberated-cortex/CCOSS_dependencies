#!/bin/bash

pushd $PWD/SDL2_mixer-2.0.4
    ./configure --prefix=$PWD/install --enable-shared=no --disable-sdltest --enable-music-opus=no --enable-music-mp3=no --enable-music-flac=no
    make
    make install
popd
