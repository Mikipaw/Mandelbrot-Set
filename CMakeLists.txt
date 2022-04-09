cmake_minimum_required(VERSION 3.20)
project(Mandelbrot)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-W -Wall -march=native")
set(CMAKE_CXX_RELEASE_FLAGS "${CMAKE_CXX_RELEASE_FLAGS} -O3 -ltbb")

add_executable(Mandelbrot mandelbrotSSE.cpp main.cpp)
target_compile_definitions(Mandelbrot PRIVATE _CRT_SECURE_NO_WARNINGS)
target_link_libraries(Mandelbrot -lOpenGL32 -lfreeGLUT)