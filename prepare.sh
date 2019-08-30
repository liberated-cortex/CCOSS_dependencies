#!/bin/bash

if `hash automake 2> /dev/null`; then
    echo "Autotools is IS installed."
else
    echo "Autotools is NOT installed. Exiting."
    exit
fi

if `hash cmake 2> /dev/null`; then
    echo "CMake is IS installed."
else
    echo "CMake is NOT installed. Exiting."
    exit
fi

./zlib.sh
./libpng.sh
./libogg.sh
./libvorbis.sh
./sndio.sh
./allegro.sh
./lua.sh
./minizip.sh
./libbsd.sh
./GorillaAudio.sh

source dirs.sh

mkdir $PWD/prepared
mkdir $PWD/prepared/include
pushd $PWD/prepared
    cp $GORILLA_AUDIO_DIR/build/build/libgorilla.a .
    cp -r $GORILLA_AUDIO_DIR/include .
    cp $ALLEGRO_DIR/install/lib/liballeg* .
    cp -r $ALLEGRO_DIR/install/include .
    cp $BSD_DIR/install/lib/libbsd.a .
    cp -r $BSD_DIR/install/include .
    cp $ZLIB_DIR/install/lib/libz.a .
    cp -r $ZLIB_DIR/install/include .
    cp $PNG_DIR/install/lib/libpng16.a .
    cp -r $PNG_DIR/install/include .
    cp $OGG_DIR/install/lib/libogg.a .
    cp -r $OGG_DIR/install/include .
    cp $VORBIS_DIR/install/lib/libvorbis.a .
    cp $VORBIS_DIR/install/lib/libvorbisenc.a .
    cp $VORBIS_DIR/install/lib/libvorbisfile.a .
    cp -r $VORBIS_DIR/install/include .
    cp $LUA_DIR/install/lib/liblua.a .
    cp -r $LUA_DIR/install/include .
    cp $MINIZIP_DIR/install/lib/libaes.a .
    cp $MINIZIP_DIR/install/lib/libminizip.a .
    cp -r $MINIZIP_DIR/install/include .
    cp $SNDIO_DIR/libsndio/libsndio.a .
popd

