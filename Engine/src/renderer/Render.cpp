#include "Render.h"

namespace Azazel
{
	std::unique_ptr<Render> Render::render(new Render());

	Render::Render()
	{

	}

	Render::~Render()
	{

	}
	
	RenderApi* Render::getRenderApi()
	{
		return nullptr;
	}

	Render* Render::getRenderer()
	{
		return render.get();
	}
	

	void Render::setClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void Render::clear(bool color, bool depth, bool stencil)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Render::drawIndexed(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader, const Texture& texture)
	{
		texture.bind();
        shader.bind();
		vertexArray.bind();
        indexBuffer.bind();
        glDrawElements(GL_TRIANGLES, indexBuffer.getElementCount() * sizeof(unsigned int), GL_UNSIGNED_INT, 0);
	}

	void Render::reset()
	{
		glEnable(GL_BLEND);
	}

	void Render::setBlendFunc()
	{

	}

	void Render::setBlendEquation()
	{
	}

}