#!/bin/bash

# This script file is used by Travis CI for continuous integration.  You, the user, do not need to run it.

mkdir -p ~/repos
mkdir -p ~/deps

echo "Cached dependencies:"
ls ~/deps

echo "Cached repos:"
ls ~/repos

clone() {
    name=$1
    url=$2
    branch=$3
    if [[ ! -e $name ]]
    then
        echo "Cloning the latest version of $name"
        git clone -q $url
        git checkout $branch

        if [[ -e $name/CMakeLists.txt ]]
        then
            echo "$url is a CMake project"
            cd $name
            cmake -DCMAKE_INSTALL_PREFIX:FILEPATH="~/deps"
            cd ..
        fi

    else
        echo "Not cloning $name, it's in the cache"
    fi
}

cd ~/repos
clone glm https://github.com/g-truc/glm.git master
clone gli https://github.com/g-truc/gli.git master
