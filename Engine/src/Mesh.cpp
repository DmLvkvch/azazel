#include "Mesh.h"

#include <vector>
#include "Vertex.h"
#include "Texture.h"

namespace Azazel
{
	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const Texture& texture)
		: texture("")
	{
		
	}

	Mesh::~Mesh()
	{

	}

	static Mesh genQuadMesh(float x, float y, float width, float height)
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

		return Mesh(vertices, indices, Texture());
	}
}