#pragma once

class IndexBuffer
{
public:

	unsigned int rendererId;

	IndexBuffer(const void* data, int size);

	~IndexBuffer();

	void bind();

	void unbind();
};