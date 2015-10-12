#!/bin/bash

case "$CC" in
    "gcc")
    SPEC=g++
    export CC=gcc-5
    export CXX=g++-5
    alias gcc=gcc-5
    alias g++=g++-5
    ;;

    "clang")
    SPEC=clang
    export CC=clang-3.8
    export CXX=clang++-3.8
    alias clang=clang-3.8
    alias clang++=clang++-3.8
    ;;
esac

alias -p
$CC --version
$CXX --version
/opt/qt55/bin/qmake ./BALLS/BALLS.pro -spec linux-$SPEC
make -s