#define _CRTDBG_MAP_ALLOC
#include<iostream>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif
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
#include <Input.h>

int main()
{
    // mem leak here
    Azazel::Application* p = Azazel::Application::getApplication();
    p->pushLayer(new Azazel::ImGuiLayer());
    p->pushLayer(new Azazel::TestLayer());
    p->pushLayer(new Azazel::GLLayer());
    p->pushLayer(new Azazel::BaseLayer());
    p->run();
    delete p;
    delete Azazel::Input::getInput();
    return 0;
}
