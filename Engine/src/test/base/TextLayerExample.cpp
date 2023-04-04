#include "TextLayerExample.h"

#include "TextureUtils.h"
#include "api/file/FileUtils.h"
#include "events/ApplicationEvent.h"
#include "IO/Input.h"
#include "render/Render.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <vector>
#include <iostream>

#include "render/renderers/TextRenderer.h"

namespace Azazel
{
    void TextLayerExample::onAttach()
    {


    }

    void TextLayerExample::onDetach()
    {

    }

    void TextLayerExample::onInputUpdate(float delta)
    {
        if (Input::getInput()->isKeyPressed(65))
        {
            camera.move({ -10.0f, 0.0f });
        }
        if (Input::getInput()->isKeyPressed(68))
        {
            camera.move({ 10.0f, 0.0f });
        }
        if (Input::getInput()->isKeyPressed(87))
        {
            camera.move({ 0.0f, 10.0f });
        }
        if (Input::getInput()->isKeyPressed(83))
        {
            camera.move({ 0.0f, -10.0f });
        }
    }

    void TextLayerExample::onUpdate(float delta)
    {
        TextRenderer::getRenderer()->draw("DIMAAAA");
    }

    void TextLayerExample::onRender(float delta)
    {
        
    }

    void TextLayerExample::onEvent(Event& e)
    {
    }
}