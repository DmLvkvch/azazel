#pragma once

#include "camera/Camera.h"
#include "camera/OrthographicCamera.h"

#include "render/Shader.h"
#include "render/Texture.h"
#include "render/VertexBuffer.h"
#include "render/IndexBuffer.h"
#include "render/VertexArray.h"
#include "render/FrameBuffer.h"
#include <map>
#include <memory>

namespace Azazel
{

    struct Character 
    {
        unsigned int textureID;
        glm::ivec2   size;
        glm::ivec2   bearing;
        unsigned int advance;
    };

    class TextRenderer
    {
        TextRenderer(const std::string& text);
        ~TextRenderer();
        void draw(const std::string& text);
    private:
        std::map<GLchar, Character> characters;
    
        std::unique_ptr<VertexArray> vertexArray;
        std::unique_ptr<Shader> textShader;
        std::unique_ptr<IndexBuffer> indexBuffer;
        std::shared_ptr<VertexBuffer> vertexBuffer;
    };
}