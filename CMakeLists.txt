cmake_minimum_required(VERSION 3.0)
project(Actions)

# Compiler settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include submodule dependencies
add_subdirectory(lib/googletest)
add_subdirectory(lib/rapidjson)

# Set up main library target and include dependency headers
add_library(${PROJECT_NAME} STATIC actions.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE lib/rapidjson/include)

# Set up unit tests target, linking against main gtest executable
add_executable(unitTests actions_test.cpp)
target_link_libraries(unitTests PUBLIC ${PROJECT_NAME} gtest_main)

# Register test with ctest
enable_testing()
add_test(NAME unitTests COMMAND unitTests)

