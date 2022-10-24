#pragma once

#include "gl_headers.h"

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Render
{
    public:
        void clear();
        void draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader);
};