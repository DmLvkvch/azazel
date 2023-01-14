#include "Application.h"
#include "imgui/ImGuiLayer.h"
#include "GLLayer.h"
#include "TestLayer.h"
#include "test/base/BaseLayer.h"
#include "test/base/TextLayerExample.h"
#include <Input.h>

int main()
{
    // mem leak here
    Azazel::Application* p = Azazel::Application::getApplication();
    p->pushLayer(new Azazel::ImGuiLayer());
    p->pushLayer(new Azazel::TestLayer());
    p->pushLayer(new Azazel::GLLayer());
    p->pushLayer(new Azazel::BaseLayer());
    p->pushLayer(new Azazel::TextLayerExample());

    p->run();
    delete p;
    return 0;
}
