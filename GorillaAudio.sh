#!/bin/bash

DIR=$PWD/GorillaAudio
SRCS="
    $DIR/src/ga.c
    $DIR/src/ga_stream.c
    $DIR/src/gau.c
    $DIR/src/common/gc_common.c
    $DIR/src/common/gc_thread.c
    $DIR/src/devices/ga_openal.c
"

OBJ_FILES=""
OBJ_DIR=$DIR/objs
if [ ! -d $OBJ_DIR ]; then
    mkdir $OBJ_DIR
fi

C_FLAGS="-DENABLE_OPENAL -g -I$DIR/include `pkg-config --cflags openal`"
for src in $SRCS; do
    path=$OBJ_DIR/$(basename $src).o
    cc $C_FLAGS -c $src -o $path
    OBJ_FILES+="$path "
done

ar rcs $DIR/libgorillaaudio.a $OBJ_FILES
