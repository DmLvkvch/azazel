#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <streambuf>

#include "Application.h"

#include "imgui/ImGuiLayer.h"

#include "GLLayer.h"
#include "TextureUtils.h"
#include "SceneNode.h"

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