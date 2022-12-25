#include "SkyBox.h"

#include "renderer/rhi/gl/gl_headers.h"
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/normal.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include <iostream>
#include <fstream>
#include <streambuf>

#include "events/KeyEvent.h"
#include "events/MouseEvent.h"
#include "events/ApplicationEvent.h"

#include <vector>

#include "renderer/rhi/gl/GLESShader.h"
#include "renderer/rhi/gl/GLESTexture.h"
#include "renderer/rhi/gl/GLESVertexBuffer.h"
#include "renderer/rhi/gl/GLESIndexBuffer.h"
#include "renderer/rhi/gl/GLESVertexArray.h"
#include "renderer/rhi/gl/GLESVertexBufferLayout.h"
#include "renderer/VertexBuffer.h"

#include "TextureUtils.h"
#include "FileUtils.h"
#include "renderer/TextureData.h"

namespace Azazel
{
	SkyBox::SkyBox()
	{

	}

	unsigned int loadCubemap(std::vector<std::string> faces)
	{
        unsigned int textureID;


        return textureID;
	}

    void SkyBox::onAttach()
    {

    }
    void SkyBox::onDetach()
    {

    }
    void SkyBox::onUpdate()
    {

    }
    
    void SkyBox::onEvent(Event& e)
    {

    }

	SkyBox::~SkyBox()
	{

	}
}