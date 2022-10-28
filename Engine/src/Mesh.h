#pragma once

#include <vector>

#include "Vertex.h"

#include "Shader.h"

class Mesh
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    Shader shader;

};