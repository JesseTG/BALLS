#!/bin/bash

$CC --version
$CXX --version
/opt/qt55/bin/qmake ./BALLS/BALLS.pro -spec linux-$SPEC
make -s -j2