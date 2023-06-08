cmake_minimum_required(VERSION 3.1)

set(STB_IMAGE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
add_library(stb_image STATIC)

target_sources( stb_image PRIVATE ${STB_IMAGE_DIR}/stb_image.cpp )

target_include_directories( stb_image PUBLIC ${STB_IMAGE_DIR}/stb_image )