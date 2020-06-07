cmake_minimum_required(VERSION 2.8.12)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(paulstretchlib_py)

add_subdirectory(../submodules/pybind11 "pybind11")
add_subdirectory(../lib "lib")

include_directories(../lib)

set(SOURCES
    module.cpp

    
	
)

pybind11_add_module(paulstretchpy  ${SOURCES})


target_link_libraries(paulstretchpy PUBLIC paulstretchlib)




