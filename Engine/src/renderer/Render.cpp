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
	

	void Render::setClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void Render::clear(bool color, bool depth, bool stencil)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}