#pragma once

class FrameBuffer
{
private:
	unsigned int rendererId;
public:
	void bind();
	void unbind();
};