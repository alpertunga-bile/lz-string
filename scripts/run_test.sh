#!/bin/bash

cmake -B build -DPXD_BUILD_TEST=ON
cmake --build build/ --config Release -j 18

cd build
ctest
cd ..
