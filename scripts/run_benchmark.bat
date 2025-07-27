@echo off

cmake -B build -DPXD_BUILD_BENCHMARK=ON
cmake --build build\ --config Release -j 18

.\build\lz_string_benchmark.exe