@echo off

cmake -B build
cmake --build build\

cd build
ctest
cd ..
