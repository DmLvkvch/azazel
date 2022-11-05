#include "GLESFrameBufferTarget.h"

Azazel::FrameBufferTarget::~FrameBufferTarget()
{
}

int Azazel::FrameBufferTarget::getWidth()
{
	return 0;
}

int Azazel::FrameBufferTarget::getHeight()
{
	return 0;
}

bool Azazel::FrameBufferTarget::isTextureTarget()
{
	return false;
}
