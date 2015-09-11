#!/bin/bash

case "$CC" in
    "gcc")
    SPEC=g++
    export CC=gcc-5
    export CXX=g++-5
    ;;

    "clang")
    SPEC=clang
    ;;
esac

qmake ./BALLS/BALLS.pro -r -spec linux-$SPEC
make