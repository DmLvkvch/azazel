#include "Render.h"

#include "rhi/gl/GLESRender.h"
#include "rhi/vulkan/VKRender.h"

#include <iostream>

// #ifdef _DEBUG
// #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// #else
// #define DBG_NEW new
// #endif
namespace Azazel
{
    std::unique_ptr<Render> Render::render;

    Render* Render::getRender()
    {
        if (!render.get())
        {
            #ifdef AZAZEL_GL
            render.reset(new GLESRender());
            #else
            render.reset(new VKRender());
            #endif
        }
        return render.get();
    }

    Render::Render()
    {
        std::cout << "Render constructor" << std::endl;
    }

    Render::~Render()
    {
        std::cout << "Render destructor" << std::endl;
    }
}