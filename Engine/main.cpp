#include "Application.h"
#include "imgui/ImGuiLayer.h"
#include "test/GLLayer.h"
#include "test/TestLayer.h"
#include "test/base/BaseLayer.h"
#include "test/base/TextLayerExample.h"
#include "test/base/ModelLoadLayer.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
    // mem leak here
    Azazel::Application* application = Azazel::Application::getApplication();

  //  application->pushLayer(new Azazel::ImGuiLayer());
    
    // application->pushLayer(new Azazel::TestLayer());
    
    // application->pushLayer(new Azazel::GLLayer());
    // application->pushLayer(new Azazel::BaseLayer());
    
    // application->pushLayer(new Azazel::TextLayerExample());
    
    application->pushLayer(new Azazel::ModelLoadLayer());

    application->run();
    delete application;
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtDumpMemoryLeaks();

    return 0;
}
