#pragma once

#include <vector>

#include "Vertex.h"

#include "Shader.h"
#include "Texture.h";

namespace Azazel
{
	class Mesh
	{
	public:
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		Texture texture;

		Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const Texture& texture);
		~Mesh();
		static Mesh genQuadMesh(float x, float y, float width, float height);
	};
}