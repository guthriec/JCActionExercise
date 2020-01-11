# Action Library

## Build and Test

Requires CMake.

Make build directory.
`mkdir build; cd build`

Run CMake.
`cmake -G 'Unix Makefiles' ..`

Build the library and its tests.
`make`

Run the tests.
`GTEST_COLOR=1 ctest -VV`
