#!/bin/bash

case "$CC" in
    "gcc")
    SPEC=g++
    export CC=gcc-5
    export CXX=g++-5
    ;;

    "clang")
    SPEC=clang
    export CC=clang-3.8
    export CXX=clang++-3.8
    ;;
esac

/opt/qt55/bin/qmake ./BALLS/BALLS.pro -spec linux-$SPEC
make -s