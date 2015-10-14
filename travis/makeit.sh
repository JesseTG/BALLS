#!/bin/bash

pushd .
name=$1
flags=$2

cd ~/repos/$name

if [[ -e ./CMakeLists.txt ]]
then
    echo "$name is a CMake project"
    cmake . $flags
elif [[ -e configure ]]
then
    echo "$name uses configure"
    ./configure $flags
fi

make -s -j2
sudo make install

popd