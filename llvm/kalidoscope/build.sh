#!/usr/bin/env bash

mkdir -p build
pushd build
    cmake ..
    make
    code=$(echo $?)
    if [[ "$code" -eq "0" ]]; then
        bin/Kalido
    fi
popd
