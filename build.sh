#!/bin/bash

VERSION="2.0.0"

mkdir -p ./build/idss-tools_${VERSION}_amd64/usr/bin/
mkdir -p ./build/idss-tools_${VERSION}_amd64/DEBIAN/
rm -rf ./build/idss-tools_${VERSION}_amd64/usr/bin/*

cmake -L .
make -j4

cp ./debian/* ./build/idss-tools_${VERSION}_amd64/DEBIAN/
cp ./build/idss-tools ./build/idss-tools_${VERSION}_amd64/usr/bin/
python3 ./python/processor.py

dpkg-deb --build ./build/idss-tools_${VERSION}_amd64
