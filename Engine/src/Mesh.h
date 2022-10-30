#pragma once

#include <vector>

#include "Vertex.h"

#include "Shader.h"
#include "Texture.h"

namespace Azazel
{
	class Mesh
	{
	public:
		std::vector<float> vertices;
		std::vector<unsigned int> indices;
		Texture texture;

		Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const Texture& texture);
		~Mesh();
		static Mesh genQuadMesh(float x, float y, float z, float width, float height);
	};
}