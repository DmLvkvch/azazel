#pragma once

#include "Camera.h"
#include "OrthographicCamera.h"

#include "Shader.h"
#include "Texture.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "FrameBuffer.h"
#include <map>
#include <memory>

namespace Azazel
{

    struct Character {
        unsigned int TextureID;
        glm::ivec2   Size;
        glm::ivec2   Bearing;
        unsigned int Advance;
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