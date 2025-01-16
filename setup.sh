#!/bin/bash

BUILD_DIR="build"

if [ ! -d "$BUILD_DIR" ];then
    echo "Creating $BUILD_DIR directory..."
    mkdir "$BUILD_DIR"
fi

cd "$BUILD_DIR" || exit

ehco "Clearing contents of $BUILD_DIR directory..."
rm -rf *

echo "Running Cmake configuration..."
cmake ../

make