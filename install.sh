#!/bin/bash

cd ~/repos/qt5

makeit() {
    name=$1

    cd ~/repos/$name

    export OLD_CC=$CC
    export OLD_CXX=$CXX

    export CC=gcc
    export CXX=g++

    make -s -j2
    sudo make install

    export CC=$OLD_CC
    export CXX=$OLD_CXX

    cd $TRAVIS_BUILD_DIR
}

makeit glm
makeit gli
