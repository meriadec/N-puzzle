#!/bin/sh

rm -rf build
cmake -H. -Bbuild
make -C build
rm -f npuzzle
ln -s build/npuzzle .
