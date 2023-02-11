#include "Render.h"

#include "ConvertUtils.h"
#include "rhi/gl/gl_cache.h"
#include "rhi/gl/GLESRender.h"
#include <iostream>

namespace Azazel
{
    std::unique_ptr<Render> Render::render(new GLESRender());

    Render* Render::getRender()
    {
        return render.get();
    }

    Render::Render()
    {
    }

    Render::~Render()
    {
    }
}