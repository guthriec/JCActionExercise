# Action Library

This is a library, namespaced "Action," currently with a single Tracker class.
It tracks info provided about different "action" strings and the time taken to complete them,
and allows users to query an average of these times for all provided actions.

## Build and Test

Requires CMake.

Make build directory:
`mkdir build; cd build`

Run CMake:
`cmake -G 'Unix Makefiles' ..`

Build the library and its tests:
`make`

Run the tests:
`GTEST_COLOR=1 ctest -VV`
