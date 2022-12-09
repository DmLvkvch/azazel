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
	
	RenderApi* Render::getRenderApi()
	{
		return this->renderApi;
	}

	Render* Render::getCurrent()
	{
		return render;
	}

	void Render::clear()
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}