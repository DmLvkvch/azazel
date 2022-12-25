#pragma once

#include <vector>

#include "Vertex.h"

#include <renderer/Texture.h>

#include <glm/glm.hpp>
#include <renderer/Shader.h>

namespace Azazel
{
	class Mesh
	{
	private:
		std::vector<float> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture*> textures;
		glm::mat4 worldTransform;
	public:

		Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
		~Mesh();
		static Mesh genQuadMesh(float x, float y, float z, float width, float height, float depth);
		static Mesh genCube(float size);

		std::vector<Vertex>& getVertices();
		std::vector<unsigned int> getIndices();
		std::vector<Texture*> getTextures();
		void draw(const Shader& shader);
	};
}