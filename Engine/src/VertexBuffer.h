#pragma once

class VertexBuffer
{
public:
	unsigned int rendererId;

	VertexBuffer(const void* data, int size);

	~VertexBuffer();

	void bind();
	void unbind();
};