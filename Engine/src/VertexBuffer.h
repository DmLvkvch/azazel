#pragma once

class VertexBuffer
{
public:
	unsigned int rendererId;

	VertexBuffer(const void* data, int size);

	~VertexBuffer();

	void bind() const;
	void unbind() const;
};