#include "Render.h"

#include "rhi/gl/GLESRender.h"

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