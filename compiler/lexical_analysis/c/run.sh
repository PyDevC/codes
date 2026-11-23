#!/usr/bin/env bash

gcc main.c -O3 -Wpedantic -Wall -Wextra -o lexer
./lexer testing.lua
echo $?
if [ "$1" == "--no-rm" ]; then
    exit 0
fi
rm ./lexer
