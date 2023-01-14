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
        
        const inline static API getAPI()
        {
            return RenderApi::api;
        }
    private:
        static API api;
    };
}