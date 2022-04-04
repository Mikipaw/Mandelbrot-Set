cmake_minimum_required(VERSION 3.20)
project(Mandelbrot)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra")

add_executable(Mandelbrot main.cpp)
target_compile_definitions(Mandelbrot PRIVATE _CRT_SECURE_NO_WARNINGS)
target_link_libraries(Mandelbrot -lOpenGL32 -lfreeGLUT)