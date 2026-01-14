#!/usr/bin/env bash

mkdir -p build
pushd build
if [[ "$1" == "cmake" ]]; then
    cmake .. -G "Unix Makefiles" -DCMAKE_DEBUG_TYPE=Debug
fi
make
bin/Solid
popd

