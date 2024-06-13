#include "Application.h"
#include "test/GLLayer.h"
#include "test/TestLayer.h"
#include "test/base/BaseLayer.h"
#include "test/base/TextLayerExample.h"
#include "test/base/ModelLoadLayer.h"
#include "window/Window.h"
#include "render/rhi/vulkan/AZContext.h"


//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

int main()
{
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    // mem leak here
    Azazel::Window* window = Azazel::Window::create();
    auto context = new Azazel::AZContext();
    context->init(*window);
    setVulkanContext(*context);

    Azazel::Application* application = new Azazel::Application(*window);
    Azazel::Application::setApplication(application);

   // application->pushLayer(new Azazel::ImGuiLayer());
    
    // application->pushLayer(new Azazel::TestLayer());
    
    // application->pushLayer(new Azazel::GLLayer());
    // application->pushLayer(new Azazel::BaseLayer());
    
   // application->pushLayer(new Azazel::ModelLoadLayer());

   // application->pushLayer(new Azazel::BaseLayer());


    application->run();
    delete application;
    delete context;
    delete window;
    //_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    //_CrtDumpMemoryLeaks();
    return 0;
}
