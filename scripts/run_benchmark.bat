@echo off

cmake -B build -DPXD_BUILD_BENCHMARK=ON
cmake --build build\ --config Release --target ALL_BUILD -j 18

.\build\Release\lz_string_benchmark.exe