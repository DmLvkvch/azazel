#pragma once

#include <vector>

#include "Vertex.h"

namespace Azazel
{
	class Mesh
	{
	public:
		std::vector<float> vertices;
		std::vector<unsigned int> indices;

		Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
		~Mesh();
		static Mesh genQuadMesh(float x, float y, float z, float width, float height);
	};
}