cmake_minimum_required(VERSION 3.1)

project(stb_image)

set(SOURCE_LIB stb_image.cpp)

add_library(stb_image STATIC ${SOURCE_LIB})