cmake_minimum_required(VERSION 3.20)
project(AED_PROJECT)

set(CMAKE_CXX_STANDARD 14)

add_executable(AED_PROJECT main.cpp cmake-build-debug/ReadFiles.cpp cmake-build-debug/ReadFiles.h)
