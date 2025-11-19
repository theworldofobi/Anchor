#!/bin/bash

# TODO - point to the correct binary locations
CMAKE=$(which cmake)
NINJA=$(which ninja)

mkdir -p ./cmake-build-release
$CMAKE -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM=$NINJA -G Ninga -S . -B ./cmake-build-release

$CMAKE --build ./cmake-build-release --target al -j 4

mkdir -p ./cmake-build-debug
$CMAKE -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MAKE_PROGRAM=$NINJA -G Ninja -S . -B ./cmake-build-debug

$CMAKE --build ./cmake-build-release --target al -j 4
