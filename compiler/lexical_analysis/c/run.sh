#!/usr/bin/env bash

gcc main.c lexer.c -o lexer
./lexer testing.lua
echo $?
