#pragma once

#include <Layer.h>

#include <renderer/OrthographicCamera.h>
#include <renderer/Shader.h>
#include <renderer/Texture.h>
#include <renderer/VertexBuffer.h>
#include <renderer/IndexBuffer.h>
#include <renderer/VertexArray.h>
#include <renderer/FrameBuffer.h>
#include <memory>


namespace Azazel
{

    struct Transform
    {
        glm::vec3 position {0.0f, 0.0f, 0.0f};
        glm::vec3 rotation {0.0f, 0.0f, 0.0f};
        glm::vec3 scale    {1.0f, 1.0f, 1.0f};
        glm::mat4 modelMatrix;

        glm::mat4 getTransformMatrix()
        {
            glm::mat4 S = glm::scale(glm::mat4(1.0f), scale);
            glm::mat4 R (1.0f);
            R = glm::rotate(R, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
            R = glm::rotate(R, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
            R = glm::rotate(R, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, -1.0f));
            glm::mat4 T (1.0f);
            T = glm::translate(T, position);
            return T * R * S;
        }
    };

    class BaseLayer : public Layer
    {
    public:
        BaseLayer()
        : Layer("Base Layer")
        {

        }

        ~BaseLayer();
        void onAttach() override;
        void onDetach() override;
        void onUpdate(float delta) override;
        void onEvent(Event& e) override;
    private:
        void drawImgui();
        void updateBlendFunc();
        void updateBlendEquation();
    private:
        OrthographicCamera camera;
        std::unique_ptr<Texture> texture;
        std::unique_ptr<Texture> texture1;
        std::unique_ptr<Shader> shader;
        std::unique_ptr<IndexBuffer> indexBuffer;
        std::unique_ptr<VertexBuffer> vertexBuffer;
        std::unique_ptr<VertexArray> vertexArray;
        Transform transform;
        glm::vec2 mousePos;
        bool rightButtonClicked = false;
    };
}