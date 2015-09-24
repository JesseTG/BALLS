#!/bin/bash

cd ~/repos/qt5

if [[ ! -e Makefile ]]
then
    mkdir -p ~/deps/qt5

    export OLD_CC=$CC
    export OLD_CXX=$CXX

    export CC=gcc
    export CXX=g++

    ./init-repository --module-subset=qtbase,qt3d,qtimageformats
    ./configure \
        -c++std c++11 \
        -confirm-license \
        -nomake examples \
        -nomake tests \
        -opensource \
        -optimized-qmake \
        -pch \
        -platform linux-g++ \
        -prefix "/home/travis/deps/qt5" \
        -hostprefix "~/deps/qt5" \
        -qt-xcb \
        -silent \
        -static \
        -no-alsa \
        -no-compile-examples \
        -no-cups \
        -no-dbus \
        -no-gstreamer \
        -no-largefile \
        -no-libproxy \
        -no-nis \
        -no-openssl \
        -no-pulseaudio \
        -no-qml-debug \
        -no-sql-mysql \
        -no-sql-psql \
        -no-sql-sqlite \
        -no-tslib \

    # The disabled libraries above will be re-enabled if:
    # cups: We implement printing of source code
    # dbus: We call on another program and it needs to talk to us
    # gstreamer: We use any sort of multimedia
    # nis/openssl/libproxy: We do any sort of networking
    # pulseaudio/alsa: We use any sort of audio
    # qml-debug: We use QML
    # sql: We keep track of data in a structured manner and QSettings won't cut it
    # tslib: We need touch screen-specific logic
    # (Can't put these comments next to the things they actually reference. Blame bash.)

    make -s -j2

    export CC=$OLD_CC
    export CXX=$OLD_CXX
fi

cd
ls -R ~/deps