#include "Render.h"

#include "rhi/gl/GLESRender.h"
#include "rhi/vulkan/VKRender.h"

namespace Azazel
{
    std::unique_ptr<Render> Render::render(nullptr);

    Render* Render::getRender()
    {
        if (render.get() == nullptr)
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
        
    }

    Render::~Render()
    {
    }
}