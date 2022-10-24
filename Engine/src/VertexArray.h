#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
public:
	unsigned int rendererId;

	VertexArray();
	~VertexArray();

	void addBuffer(VertexBuffer& vb, const VertexBufferLayout& layout);

	void bind() const;
	void unbind() const;
};