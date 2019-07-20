#!/bin/bash

pushd $PWD/GorillaAudio
    cd build
    mkdir build
    cd build
    cmake -DCMAKE_BUILD_TYPE=RelWithDebugInfo ../
    make -j$(nproc)
popd
