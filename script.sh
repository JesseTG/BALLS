#!/bin/bash

case "$CC" in
    "gcc"   ) SPEC=g++   ;;
    "clang" ) SPEC=clang ;;
esac

qmake ./BALLS/BALLS.pro -r -spec linux-$SPEC
make