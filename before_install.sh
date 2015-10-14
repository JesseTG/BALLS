#!/bin/bash

# This script file is used by Travis CI for continuous integration.  You, the user, do not need to run it.

pushd .
mkdir -p ~/repos

clone() {
    pushd .

    cd ~/repos

    name=$1
    url=$2
    branch=$3
    flags=$4

    echo "Cloning the latest version of $name"
    git clone -q $url

    cd $name
    git checkout -q $branch

    if [[ -e ./CMakeLists.txt ]]
    then
        echo "$url is a CMake project"
        cmake . $flags
    elif [[ -e configure ]]
    then
        echo "$url uses configure"
        ./configure $flags
    fi

    popd
}

sudo add-apt-repository -y 'deb http://llvm.org/apt/jessie/ llvm-toolchain-jessie-3.7 main'
sudo add-apt-repository -y 'deb http://ppa.launchpad.net/beineri/opt-qt55-trusty/ubuntu trusty main'
sudo apt-get -qqy update
sudo apt-get install --no-install-recommends --force-yes --no-upgrade -qqy $COMMON_PACKAGES $PLATFORM_PACKAGES
sudo chmod -f +x /opt/qt55/bin/qt55-env.sh
/opt/qt55/bin/qt55-env.sh

if [[ $CC == *"gcc"* ]]; then
    sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-5 100
    sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-5 100

    sudo update-alternatives --auto g++
    sudo update-alternatives --auto gcc
elif [[ $CC == *"clang"* ]]; then
    sudo update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-3.7 100
    sudo update-alternatives --install /usr/bin/clang clang /usr/bin/clang-3.7 100
    sudo update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang++ 1000

    sudo update-alternatives --auto clang++
    sudo update-alternatives --auto clang
    sudo update-alternatives --auto c++
fi

clone glm https://github.com/g-truc/glm.git master
clone gli https://github.com/g-truc/gli.git master
# clone qt5 http://code.qt.io/qt/qt5.git 5.6

popd