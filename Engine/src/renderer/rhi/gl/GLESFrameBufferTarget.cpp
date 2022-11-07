#include "GLESFrameBufferTarget.h"

namespace Azazel
{

	FrameBufferTarget::~FrameBufferTarget()
	{
	}

	int FrameBufferTarget::getWidth()
	{
		return 0;
	}

	int FrameBufferTarget::getHeight()
	{
		return 0;
	}

	bool FrameBufferTarget::isTextureTarget()
	{
		return false;
	}
}