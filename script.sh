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

~/deps/qt5/qtbase/bin/qmake ./BALLS/BALLS.pro -r -spec linux-$SPEC INCLUDEPATH+="~/deps/qt5/include" LIBS+="~/deps/qt5/libs"
make -s