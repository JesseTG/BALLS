#!/bin/bash

# This script file is used by Travis CI for continuous integration.  You, the user, do not need to run it.

mkdir -p ~/repos
cd ~/repos
echo "Cached repos:"
ls

clone() {
    name=$1
    url=$2
    if [[ ! -e $name ]]
    then
        echo "Cloning the latest version of $name"
        git clone -q $url

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

clone glm https://github.com/g-truc/glm.git
clone gli https://github.com/g-truc/gli.git