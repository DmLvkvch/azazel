#include <iostream>
#include <fstream>
#include <streambuf>

#include "Application.h"

#include "imgui/ImGuiLayer.h"
#include "GLLayer.h"
#include "TestLayer.h"
#include "test/base/BaseLayer.h"
const unsigned int SCR_WIDTH = 940;
const unsigned int SCR_HEIGHT = 560;

int main()
{
    Azazel::Application* p = Azazel::Application::createApplication();
    p->pushLayer(new Azazel::ImGuiLayer());
    p->pushLayer(new Azazel::TestLayer());
   // p->pushLayer(new Azazel::GLLayer());
    Azazel::Layer* l = new Azazel::BaseLayer();
    p->pushLayer(l);
    p->run();
    delete p;
    return 0;
}