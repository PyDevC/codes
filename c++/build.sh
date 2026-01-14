#!/usr/bin/env bash

pushd build
cmake .. -G "Unix Makefiles" -DCMAKE_DEBUG_TYPE=Debug
make
bin/Solid
popd

