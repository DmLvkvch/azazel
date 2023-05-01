cmake_minimum_required( VERSION 3.1 )

project(Engine VERSION 1.0)

find_package(OpenGL REQUIRED)
find_package (Vulkan REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only")

add_definitions(-DAZAZEL_GL)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

include_directories ("vendor/glad/include"
                     "vendor/glfw"
                     "vendor/glm"
                     "vendor/freetype"
                     "vendor/imgui/imgui"
                     "vendor/imgui/imgui/backends"
                     "vendor/assimp"
                     "vendor/stb_image"
                     "vendor/json/include"
                     "src")

OPTION (ASSIMP_BUILD_TESTS "If the test suite for Assimp is built in addition to the library." OFF)
OPTION (ASSIMP_WARNINGS_AS_ERRORS "Treat all warnings as errors." OFF)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/stb_image)
add_subdirectory(vendor/freetype)
add_subdirectory(vendor/assimp)
add_subdirectory(vendor/imgui)

if (APPLE)
    set(CMAKE_C_ARCHIVE_FINISH   "<CMAKE_RANLIB> -no_warning_for_no_symbols -c <TARGET>")
    set(CMAKE_CXX_ARCHIVE_FINISH "<CMAKE_RANLIB> -no_warning_for_no_symbols -c <TARGET>")
endif()

if(MSVC)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup")
endif()

file(GLOB_RECURSE ENGINE_SRC
    ${CMAKE_SOURCE_DIR}/src/*.c
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)
    
file(GLOB_RECURSE ENGINE_HEADERS 
    ${CMAKE_SOURCE_DIR}/src/*.h
    ${CMAKE_SOURCE_DIR}/src/*.hpp
)

add_executable(${PROJECT_NAME} "main.cpp" ${ENGINE_HEADERS} ${ENGINE_SRC})

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
endif ()

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} Vulkan::Vulkan glfw assimp stb_image glad glm::glm freetype IMGUI OpenGL::GL)

file(REMOVE ${CMAKE_BINARY_DIR}/shaders)
file(REMOVE ${CMAKE_BINARY_DIR}/images)
file(REMOVE ${CMAKE_BINARY_DIR}/textures)
file(REMOVE ${CMAKE_BINARY_DIR}/fonts)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/shaders/ DESTINATION ${CMAKE_BINARY_DIR}/shaders)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/images/ DESTINATION ${CMAKE_BINARY_DIR}/images)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/textures/ DESTINATION ${CMAKE_BINARY_DIR}/textures)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/fonts/ DESTINATION ${CMAKE_BINARY_DIR}/fonts)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/objects/ DESTINATION ${CMAKE_BINARY_DIR}/objects)