#!/bin/bash

SDL_PREFIX=$PWD/SDL2-2.0.9
pushd $PWD/SDL2_mixer-2.0.4
    ./configure --prefix=$PWD/install --enable-shared=no --disable-sdltest --enable-music-opus=no --enable-music-mp3=no --enable-music-flac=no --with-sdl-prefix=$SDL_PREFIX/install
    make
    make install
popd
