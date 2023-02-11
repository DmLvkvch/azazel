#include "TextLayerExample.h"

#include "TextureUtils.h"
#include "FileUtils.h"
#include "events/KeyEvent.h"
#include "events/MouseEvent.h"
#include "events/ApplicationEvent.h"
#include "Input.h"
#include "render/Render.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include <vector>
#include <iostream>

namespace Azazel
{
    void TextLayerExample::onAttach()
    {

        camera = OrthographicCamera(-400.0f, 400.0f, -400.00f, 400.0f, -1.0f, 1.0f);
        shader.reset(Shader::create(FileUtils::readFile("shaders/2d/text.vert.glsl"), FileUtils::readFile("shaders/2d/text.frag.glsl")));

        FT_Library ft;
        if (FT_Init_FreeType(&ft))
        {
            std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
            return;
        }

        FT_Face face;
        if (FT_New_Face(ft, "fonts/Arial.ttf", 0, &face)) {
            std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
            return;
        }
        FT_Set_Pixel_Sizes(face, 0, 24);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        for (unsigned char c = 0; c < 128; c++)
        {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            Character character 
            {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
            };
            characters.insert(std::pair<char, Character>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);
        FT_Done_Face(face);
        FT_Done_FreeType(ft);

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) 8);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void TextLayerExample::onDetach()
    {

    }

    void TextLayerExample::onInputUpdate(float delta)
    {
        if (Input::getInput()->isKeyPressed(65))
        {
            camera.move({ -10.0f, 0.0f });
        }
        if (Input::getInput()->isKeyPressed(68))
        {
            camera.move({ 10.0f, 0.0f });
        }
        if (Input::getInput()->isKeyPressed(87))
        {
            camera.move({ 0.0f, 10.0f });
        }
        if (Input::getInput()->isKeyPressed(83))
        {
            camera.move({ 0.0f, -10.0f });
        }
    }

    void TextLayerExample::onUpdate(float delta)
    {
        shader->bind();
        shader->setMatrix4f("u_mvp", camera.getViewProjectionMatrix() * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f)));
    }

    void TextLayerExample::onRender(float delta)
    {
        Render::getRender()->setBlend(true);
        Render::getRender()->setBlendFunc(BlendFunction::SrcAlpha, BlendFunction::OneMinusSrcAlpha);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(VAO);

        std::string text = "DIMA DIMA DIMA";
        float x = 0.0f;
        float y = 0.0f;
        float scale = 1.0f;
        for (auto c : text) 
        {
            Character ch = characters[c];

            float xpos = x + ch.bearing.x * scale;
            float ypos = y - (ch.size.y - ch.bearing.y) * scale;

            float w = ch.size.x * scale;
            float h = ch.size.y * scale;
            float vertices[6][4] = {
                { xpos,     ypos + h, 0.0f, 0.0f },
                { xpos,     ypos,     0.0f, 1.0f },
                { xpos + w, ypos,     1.0f, 1.0f },

                { xpos,     ypos + h, 0.0f, 0.0f },
                { xpos + w, ypos,     1.0f, 1.0f },
                { xpos + w, ypos + h, 1.0f, 0.0f }          
            };
            glBindTexture(GL_TEXTURE_2D, ch.textureID);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            x += (ch.advance >> 6) * scale;
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void TextLayerExample::onEvent(Event& e)
    {
        if (e.getEventType() == EventType::MouseScrolled)
        {
            MouseScrollEvent& k = *(MouseScrollEvent*)(&e);
        }
    }
}