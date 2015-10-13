#!/bin/bash

case "$CC" in
    "gcc")
    SPEC=g++
    ;;

    "clang")
    SPEC=clang
    ;;
esac


$CC --version
$CXX --version
/opt/qt55/bin/qmake ./BALLS/BALLS.pro -spec linux-$SPEC
make -s