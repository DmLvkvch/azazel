#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace Azazel
{
	enum Semantic
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

	enum ElementType
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

	int sizeOfElement(const ElementType& el);

	class Element
	{
	public:
		Semantic semantic;
		ElementType elementType;
		int dimension;
		int size;
		int offset;
		int id;

		Element(Semantic& semantic, int dimension, ElementType& elementType)
		{
			this->semantic = semantic;
			this->dimension = dimension;
			this->elementType = elementType;
		}
	};

	class Vertex
	{
	public:

		std::vector<Element>& elements;
		int size;

		Vertex(std::vector<Element>& elements)
		: elements(elements)
		{
			this->size = computeSize(elements);
		}
		virtual ~Vertex()
		{
			
		}
	private:
		int computeSize(const std::vector<Element>& elements)
		{
			int size = 0;
			for (auto& element : elements)
			{
				size += element.size;
			}
			return size;
		}
	};
}