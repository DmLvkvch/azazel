#pragma once

#include <vector>

#include "Vertex.h"

#include <renderer/Texture.h>

#include <glm/glm.hpp>

namespace Azazel
{
	class Mesh
	{
	private:
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture*> textures;
		glm::mat4 worldTransform;
	public:

		Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
		~Mesh();
		static Mesh genQuadMesh(float x, float y, float z, float width, float height);
		static Mesh genCube(float size);

		std::vector<Vertex>& getVertices();
		std::vector<unsigned int> getIndices();
		std::vector<Texture*> getTextures();
	};
}