cmake_minimum_required(VERSION 3.1)

project(MyProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE_EXE main.cpp)	

include_directories(include)

add_executable(main ${SOURCE_EXE})

add_subdirectory(include)	

add_subdirectory(source)

target_link_libraries(main Lib)	