#include "GLLayer.h"

#include "events/KeyEvent.h"
#include "events/MouseEvent.h"
#include "events/ApplicationEvent.h"
#include "TextureUtils.h"
#include "api/file/FileUtils.h"
#include "render/TextureData.h"
#include "render/Render.h"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/normal.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include <iostream>
#include <vector>
#include "render/MeshHelper.h"
#include "render/ModelHelper.h"

namespace Azazel
{
    
    void GLLayer::onAttach()
    {

        model = ModelHelper::cube();
        auto textureData = TextureUtils::loadTexture("images/container2.png");
        this->face.reset(Texture::create(textureData));
        TextureUtils::freeTextureData(textureData);
        
        shader.reset(Shader::create(FileUtils::readFile("shaders/default.vert.glsl"), FileUtils::readFile("shaders/default.frag.glsl")));

        testShader.reset(Shader::create(FileUtils::readFile("shaders/circle.vert.glsl"), FileUtils::readFile("shaders/circle.frag.glsl")));
        
        gridMesh = MeshHelper::genQuadMesh();

        orthographicCamera = OrthographicCamera(-2.0f, 2.0f, -2.0f, 2.0f);
    }

    void GLLayer::onDetach()
    {

    }
    
    void GLLayer::onUpdate(float delta)
    {
        ImGui::Begin("Transform");
        ImGui::SliderFloat2("circle", &r.x, 0.0, 1.0f);
        ImGui::End();

        glm::mat4 mvp = orthographicCamera.getViewProjectionMatrix();
        testShader->bind();
        testShader->setMatrix4f("u_mvp", mvp)->setFloat("u_radius", r.x)->setFloat("u_thickness", r.y);
       // gridMesh.draw(*testShader);
       // mvp = orthographicCamera.getViewProjectionMatrix() * glm::translate(glm::mat4(1.0f), glm::vec3{0.1f, 0.3f, 0.0f}) * glm::rotate(glm::mat4(1.0f), glm::radians((float) glfwGetTime()* 10.0f), {1.0f, 0.0f, 1.0f}) * glm::scale(glm::mat4(1.0f), {0.4f, 0.40f, 0.4f});
       
        Render::getRender()->setDepthTest(true);
        shader->bind();
        shader->setInt("u_texture_0", 0)->setMatrix4f("u_mvp", mvp);
        face->bind();
        model.draw(*shader);
        Render::getRender()->setDepthTest(false);
    }
    
    void GLLayer::onEvent(Event& e)
    {
    }
}