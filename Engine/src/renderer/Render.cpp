#include "Render.h"

namespace Azazel
{
	Render* Render::render = new Render();

	Render::Render()
	{

	}

	Render::~Render()
	{

	}

	TextureRHI* Render::createTextureRHI(const Texture* texture)
	{
		return renderApi->createTextureRHI(texture);
	}

	
	RenderApi* Render::getRenderApi()
	{
		return this->renderApi;
	}

	Render* Render::getCurrent()
	{
		return render;
	}
}