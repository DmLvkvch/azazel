#pragma once

#include "Layer.h"
#include "camera/OrthographicCamera.h"
#include "renderer/Shader.h"
#include "renderer/Texture.h"
#include "renderer/VertexBuffer.h"
#include "renderer/IndexBuffer.h"
#include "renderer/VertexArray.h"
#include "renderer/FrameBuffer.h"
#include <memory>
#include <map>

namespace Azazel
{
    struct Character {
        unsigned int textureID;
        glm::ivec2   size;
        glm::ivec2   bearing;
        unsigned int advance;
    };
        
    class TextLayerExample : public Layer
    {
    public:
        TextLayerExample() : Layer("Text Layer") {}
        ~TextLayerExample() {}

        void onAttach() override;
        void onDetach() override;
        void onInputUpdate(float delta) override;
        void onUpdate(float delta) override;
        void onRender(float delta) override;
        void onEvent(Event& e) override;
 
    private:
        std::map<GLchar, Character> characters;

        unsigned int VAO, VBO;
        OrthographicCamera camera;
        std::unique_ptr<Shader> shader;
        std::unique_ptr<VertexArray> vertexArray;
        std::unique_ptr<IndexBuffer> indexBuffer;
        std::unique_ptr<Texture> texture;
    };
}