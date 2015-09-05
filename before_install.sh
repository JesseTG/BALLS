#!/bin/bash

# This script file is used by Travis CI for continuous integration.  You, the user, do not need to run it.

mkdir -p ~/repos
cd ~/repos
ls
if [[ ! -e glm ]]
then
    git clone https://github.com/g-truc/glm.git
fi

if [[ ! -e glm/CMakeCache.txt ]]
then
    cd glm
    cmake -DCMAKE_INSTALL_PREFIX:FILEPATH="~/deps"
fi