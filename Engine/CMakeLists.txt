cmake_minimum_required( VERSION 3.1 )

project(Engine VERSION 1.0)

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only")

include_directories ("vendor/glad/include"
                     "vendor/glfw"
                     "vendor/glm"
                     "vendor/freetype"
                     "vendor/imgui"
                     "vendor/imgui/backends"
                     "vendor"
                     "src")

add_subdirectory(vendor/glad)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/stb_image)
add_subdirectory(vendor/freetype)
add_subdirectory(vendor/imgui)

if(MSVC)
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup")
endif()

file(GLOB_RECURSE ENGINE_SRC
    ${CMAKE_SOURCE_DIR}/src/*.c
    ${CMAKE_SOURCE_DIR}/src/*.cpp)
    
file(GLOB_RECURSE ENGINE_HEADERS 
    ${CMAKE_SOURCE_DIR}/src/*.h
    ${CMAKE_SOURCE_DIR}/src/*.hpp)


add_executable(${PROJECT_NAME} "main.cpp" ${ENGINE_HEADERS} ${ENGINE_SRC})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glfw stb_image glad glm::glm freetype IMGUI)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/res/shaders/ DESTINATION ${CMAKE_BINARY_DIR}/shaders)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/res/images/ DESTINATION ${CMAKE_BINARY_DIR}/images)