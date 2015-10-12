#!/bin/bash

# This script file is used by Travis CI for continuous integration.  You, the user, do not need to run it.

mkdir -p ~/repos

clone() {
    name=$1
    url=$2
    branch=$3
    flags=$4

    echo "Cloning the latest version of $name"
    git clone -q $url

    cd $name
    git checkout -q $branch

    if [[ -e $name/CMakeLists.txt ]]
    then
        echo "$url is a CMake project"
        cmake $flags >/dev/null
    elif [[ -e $name/configure ]]
    then
        echo "$url uses configure"
        ./configure $flags
    fi

    cd ..
}

cd ~/repos

clone glm https://github.com/g-truc/glm.git master
clone gli https://github.com/g-truc/gli.git master
# clone qt5 http://code.qt.io/qt/qt5.git 5.6

cd