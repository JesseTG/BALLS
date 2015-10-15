#!/bin/bash

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

popd