cmake_minimum_required(VERSION 3.0)
project(Actions)
enable_testing()
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SOURCE actions.cpp)
add_subdirectory(lib/googletest)
add_subdirectory(lib/rapidjson)

add_library(${PROJECT_NAME} STATIC ${SOURCE} lib/rapidjson/include)
target_include_directories(${PROJECT_NAME} PRIVATE lib/rapidjson/include)

add_executable(unitTests actions_test.cpp)

add_test(NAME unitTests COMMAND unitTests)

target_link_libraries(unitTests PUBLIC ${PROJECT_NAME} gtest gtest_main)
