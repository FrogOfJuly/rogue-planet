cmake_minimum_required(VERSION 3.19)
project(earthcooling)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(deps/pybind11)

pybind11_add_module(earthcooling
        wrapper.cpp
        find_alpha.cpp
        engine.cpp
        engine.h)

#add_executable(earthcooling_test
#        test.cpp
#        find_alpha.cpp
#        engine.cpp
#        engine.h)