#!/bin/bash

case "$CC" in
    "gcc")
    SPEC=g++
    alias gcc=gcc-5
    alias g++=g++-5
    export CC=gcc-5
    export CXX=g++-5
    ;;

    "clang")
    SPEC=clang
    alias clang=clang-3.7
    alias clang++=clang++-3.7
    export CC=clang-3.7
    export CXX=clang++-3.7
    ;;
esac

alias -p
$CC --version
$CXX --version
/opt/qt55/bin/qmake ./BALLS/BALLS.pro -spec linux-$SPEC
make -s