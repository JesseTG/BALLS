#!/bin/bash

makeit() {
    pushd .
    name=$1

    cd ~/repos/$name

    make -s -j2
    sudo make install

    popd
}

makeit glm
makeit gli
