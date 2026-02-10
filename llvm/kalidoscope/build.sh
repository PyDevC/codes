#!/usr/bin/env bash

if [[ "$1" == "fmt" ]]; then
    clang-format -i src/*.cpp
fi

mkdir -p build
pushd build
    cmake .. -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
    make
    code=$(echo $?)
    if [[ "$code" -eq "0" ]]; then
        bin/Kalido
    fi
popd
