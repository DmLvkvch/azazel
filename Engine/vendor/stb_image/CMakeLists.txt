cmake_minimum_required(VERSION 3.1)

project(stb_image)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/stb_image/stb_image.h DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE_LIB stb_image.cpp)

add_library(stb_image STATIC ${SOURCE_LIB})