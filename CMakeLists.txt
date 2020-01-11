cmake_minimum_required(VERSION 3.0)
project(Actions)
enable_testing()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -pedantic")
set(SOURCE actions.cpp)
add_library(${PROJECT_NAME} STATIC ${SOURCE})
add_subdirectory(lib/googletest)

add_executable(unitTests actions_test.cpp)

add_test(NAME unitTests COMMAND unitTests)

target_link_libraries(unitTests PUBLIC ${PROJECT_NAME} gtest gtest_main)
