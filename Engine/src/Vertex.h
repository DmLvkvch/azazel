#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

class Vertex
{
private:
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 texCoords;

public:
	Vertex();
	~Vertex();
};