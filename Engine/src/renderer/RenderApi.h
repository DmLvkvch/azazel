#pragma once

#include <renderer/Texture.h>
#include <renderer/VertexArray.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include <memory>

namespace Azazel
{
    class RenderApi
    {
    public: 
        enum class API
        {
            None = 0, OpenGL = 1
        };

        RenderApi();

        virtual ~RenderApi();
        virtual void clear() = 0;
        virtual void setClearColor(const glm::vec4 color) = 0;
        virtual void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;
        
        const inline static API getAPI()
        {
            return RenderApi::api;
        }
    private:
        static API api;
    };
}