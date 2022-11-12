#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace Azazel
{

	enum class Semantic
	{
		POSITION,
		COLOR,
		TEX_COORD,
		NORMAL,
		TANGENT,
		BINORMAL,
		ASHIFT,
		AGAMMA
	};

	enum class ElementType
	{
		FLOAT,
		HALF,
		BYTE,
		UNSIGNED_BYTE,
		INT,
		UNSIGNED_INT,
		SHORT,
		UNSIGNED_SHORT
	};

	class Element
	{
	public:
		Semantic semantic;
		ElementType elementType;
		int dimension;
		int size;
		int offset;
		int id;
	};

	class Vertex
	{
	public:

		std::vector<Element>& elements;
		int size;

		Vertex(std::vector<Element>& elements)
		: elements(elements)
		{

		}
		virtual ~Vertex()
		{
			
		}
	private:
		int computeSize(std::vector<Element>& elements)
		{
			int size = 0;
			return size;
		}
	};
}