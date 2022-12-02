#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <streambuf>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/normal.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include "Mesh.h"
#include "Camera.h"

#include "events/Event.h"
#include "events/KeyEvent.h"
#include "events/ApplicationEvent.h"

#include "renderer/rhi/gl/GLESTexture.h"
#include "renderer/rhi/gl/GLESShader.h"
#include "renderer/rhi/gl/GLESIndexBuffer.h"
#include "renderer/rhi/gl/GLESVertexBuffer.h"
#include "renderer/rhi/gl/GLESVertexArray.h"
#include "renderer/rhi/gl/GLESVertexBufferLayout.h"

#include "Application.h"

#include "imgui/ImGuiLayer.h"

#include "GLLayer.h"

#include "Vertex.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, Azazel::Camera& camera);

const unsigned int SCR_WIDTH = 940;
const unsigned int SCR_HEIGHT = 560;

using namespace Azazel;

std::string readFile(const std::string& file)
{
    std::fstream stream (file);
    if (!stream.is_open()) {
        std::cout << "Could not open the file - '" << file << "'" << std::endl;
    }
    return std::string((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
}

int main()
{
    Application* p = Application::createApplication();
    p->pushLayer(new ImGuiLayer());
    p->pushLayer(new GLLayer());
    p->run();
    delete p;
    return 0;
}

void processInput(GLFWwindow* window, Camera& camera)
{

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}