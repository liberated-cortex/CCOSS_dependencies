#!/bin/bash
source dirs.sh

pushd $GORILLA_AUDIO_DIR
    cd build
    mkdir build
    cd build
    cmake -DCMAKE_BUILD_TYPE=RelWithDebugInfo ../
    make -j$(nproc)
popd
