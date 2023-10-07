#include "Application.h"
#include "imgui/ImGuiLayer.h"
#include "test/GLLayer.h"
#include "test/TestLayer.h"
#include "test/base/BaseLayer.h"
#include "test/base/TextLayerExample.h"
#include "test/base/ModelLoadLayer.h"

int main()
{
   // _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    // mem leak here
    Azazel::Application* application = Azazel::Application::getApplication();

   // application->pushLayer(new Azazel::ImGuiLayer());
    
    // application->pushLayer(new Azazel::TestLayer());
    
    // application->pushLayer(new Azazel::GLLayer());
    // application->pushLayer(new Azazel::BaseLayer());
    
    
   // application->pushLayer(new Azazel::ModelLoadLayer());

   // application->pushLayer(new Azazel::BaseLayer());


    application->run();
    delete application;

    return 0;
}
