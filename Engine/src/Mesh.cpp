#include "Mesh.h"

#include <vector>
#include "Vertex.h"

namespace Azazel
{
	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
		: vertices(vertices), indices(indices)
	{
		
	}

	Mesh::~Mesh()
	{

	}

	Mesh Mesh::genQuadMesh(float x, float y, float z, float width, float height)
	{
		std::vector<Vertex> vertices ;
		
		std::vector<unsigned int> indices {0, 1, 2, 0, 2, 3};

		return Mesh(vertices, indices);
	}

	Mesh Mesh::genCube(float size)
	{
		float left = 1; 
		float top = 1; 
		float front = 1; 
		float bottom = 1; 
		float back = 1; 
		float right = 1; 

		std::vector<glm::vec3> positions = {
			glm::vec3(-left, top, front), // 0
			glm::vec3(-left, -bottom, front), // 1
			glm::vec3(-left, top, -back), // 2
			glm::vec3(-left, -bottom, -back), // 3
			glm::vec3(right, top, front), // 4
			glm::vec3(right, -bottom, front), // 5
			glm::vec3(right, top, -back), // 6
			glm::vec3(right, -bottom, -back), // 7
		};

		std::vector<glm::vec3> vertices;
		vertices.push_back(positions[4]);
		vertices.push_back(positions[2]);
		vertices.push_back(positions[0]);
		vertices.push_back(positions[2]);
		vertices.push_back(positions[7]);
		vertices.push_back(positions[3]);
		vertices.push_back(positions[6]);
		vertices.push_back(positions[5]);
		vertices.push_back(positions[7]);
		vertices.push_back(positions[1]);
		vertices.push_back(positions[7]);
		vertices.push_back(positions[5]);
		vertices.push_back(positions[0]);
		vertices.push_back(positions[3]);
		vertices.push_back(positions[1]);
		vertices.push_back(positions[4]);
		vertices.push_back(positions[1]);
		vertices.push_back(positions[5]);
		vertices.push_back(positions[4]);
		vertices.push_back(positions[6]);
		vertices.push_back(positions[2]);
		vertices.push_back(positions[2]);
		vertices.push_back(positions[6]);
		vertices.push_back(positions[7]);
		vertices.push_back(positions[6]);
		vertices.push_back(positions[4]);
		vertices.push_back(positions[5]);
		vertices.push_back(positions[1]);
		vertices.push_back(positions[3]);
		vertices.push_back(positions[7]);
		vertices.push_back(positions[0]);
		vertices.push_back(positions[2]);
		vertices.push_back(positions[3]);
		vertices.push_back(positions[4]);
		vertices.push_back(positions[0]);
		vertices.push_back(positions[1]);

		std::vector<glm::vec2> texC;

		texC.push_back(glm::vec2(1.0f, 0.0f));
		texC.push_back(glm::vec2(0.0f, 1.0f));
		texC.push_back(glm::vec2(0.0f, 0.0f));
		texC.push_back(glm::vec2(1.0f, 1.0f));
		texC.push_back(glm::vec2(0.0f, 0.0f));
		texC.push_back(glm::vec2(1.0f, 0.0f));
		texC.push_back(glm::vec2(1.0f, 1.0f));
		texC.push_back(glm::vec2(0.0f, 0.0f));
		texC.push_back(glm::vec2(1.0f, 0.0f));
		texC.push_back(glm::vec2(0.0f, 1.0f));
		texC.push_back(glm::vec2(1.0f, 0.0f));
		texC.push_back(glm::vec2(1.0f, 1.0f));
		texC.push_back(glm::vec2(1.0f, 1.0f));
		texC.push_back(glm::vec2(0.0f, 0.0f));
		texC.push_back(glm::vec2(1.0f, 0.0f));
		texC.push_back(glm::vec2(1.0f, 1.0f));
		texC.push_back(glm::vec2(0.0f, 0.0f));
		texC.push_back(glm::vec2(1.0f, 0.0f));
		texC.push_back(glm::vec2(1.0f, 0.0f));
		texC.push_back(glm::vec2(1.0f, 1.0f));
		texC.push_back(glm::vec2(0.0f, 1.0f));
		texC.push_back(glm::vec2(1.0f, 1.0f));
		texC.push_back(glm::vec2(0.0f, 1.0f));
		texC.push_back(glm::vec2(0.0f, 0.0f));
		texC.push_back(glm::vec2(1.0f, 1.0f));
		texC.push_back(glm::vec2(0.0f, 1.0f));
		texC.push_back(glm::vec2(0.0f, 0.0f));
		texC.push_back(glm::vec2(0.0f, 1.0f));
		texC.push_back(glm::vec2(0.0f, 0.0f));
		texC.push_back(glm::vec2(1.0f, 0.0f));
		texC.push_back(glm::vec2(1.0f, 1.0f));
		texC.push_back(glm::vec2(0.0f, 1.0f));
		texC.push_back(glm::vec2(0.0f, 0.0f));
		texC.push_back(glm::vec2(1.0f, 1.0f));
		texC.push_back(glm::vec2(0.0f, 1.0f));
		texC.push_back(glm::vec2(0.0f, 0.0f));
		return genQuadMesh(0,0,0,0,0);
	}
}