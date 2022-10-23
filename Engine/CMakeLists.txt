cmake_minimum_required( VERSION 3.1 )

project(Engine VERSION 1.0)

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only")

include_directories ("vendor/glad/include"
                     "vendor/glfw"
                     "vendor" 
                     "src")

add_subdirectory (glad)
add_subdirectory(glfw)

if(MSVC)
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup")
endif()

add_executable(${PROJECT_NAME} "main.cpp" "src/Shader.cpp" "src/VertexBuffer.cpp" "src/IndexBuffer.cpp" "src/Texture.cpp" "src/VertexArray.h" "src/VertexArray.cpp" "src/VertexBufferLayout.h" "src/gl_headers.h" "vendor/stb_image.cpp")

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glfw glad)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/res/shaders/ DESTINATION ${CMAKE_BINARY_DIR}/shaders)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/res/images/ DESTINATION ${CMAKE_BINARY_DIR}/images)