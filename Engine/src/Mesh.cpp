#include "Mesh.h"

#include <vector>
#include "Vertex.h"

namespace Azazel
{
	Mesh::Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices)
		: vertices(vertices), indices(indices)
	{
		
	}

	Mesh::~Mesh()
	{

	}

	Mesh Mesh::genQuadMesh(float x, float y, float z, float width, float height)
	{
		std::vector<float> vertices {x,         y,          z, 0.0, 0.0,
									 x,         y + height, z, 0.0, 1.0,
									 x + width, y + height, z, 1.0, 1.0,
									 x + width, y,          z, 1.0, 0.0};
		
		std::vector<unsigned int> indices {0, 1, 2, 0, 2, 3};

		return Mesh(vertices, indices);
	}
}