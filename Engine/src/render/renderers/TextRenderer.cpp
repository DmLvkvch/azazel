#include "TextRenderer.h"

#include "render/Render.h"
#include "api/file/FileUtils.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>

namespace Azazel
{
    TextRenderer::TextRenderer()
    {
        camera = OrthographicCamera(-400.0f, 400.0f, -400.00f, 400.0f, -1.0f, 1.0f);
        textShader.reset(Shader::create(FileUtils::readFile("shaders/2d/text.vert.glsl"), FileUtils::readFile("shaders/2d/text.frag.glsl")));

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
        vertexArray.reset(VertexArray::create());
        vertexBuffer.reset(VertexBuffer::create(nullptr, sizeof(float) * 6 * 5));
        vertexArray->addBuffer(vertexBuffer, Vertex_P3_T2::bufferLayout);
    }

    TextRenderer* TextRenderer::getRenderer()
    {
        if (!TextRenderer::textRenderer.get())
        {
            TextRenderer::textRenderer.reset(new TextRenderer());
        }
        return TextRenderer::textRenderer.get();
    }
    
    TextRenderer::~TextRenderer()
    {
    
    }

    void TextRenderer::onUpdate(float delta)
    {
    }

    void TextRenderer::draw(const std::string& text)
    {   
        textShader->bind();
        textShader->setMatrix4f("u_mvp", camera.getViewProjectionMatrix());
        Render::getRender()->setBlend(true);
        Render::getRender()->setBlendFunc(BlendFunction::SRC_ALPHA, BlendFunction::ONE_MINUS_SRC_ALPHA);
        glActiveTexture(GL_TEXTURE0);
        vertexArray->bind();

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
            float vertices[6][5] {
                { xpos,     ypos + h, 0.0f, 0.0f, 0.0f },
                { xpos,     ypos,     0.0f, 0.0f, 1.0f },
                { xpos + w, ypos,     0.0f, 1.0f, 1.0f },

                { xpos,     ypos + h, 0.0f, 0.0f, 0.0f },
                { xpos + w, ypos,     0.0f, 1.0f, 1.0f },
                { xpos + w, ypos + h, 0.0f, 1.0f, 0.0f }          
            };
            glBindTexture(GL_TEXTURE_2D, ch.textureID);
            vertexBuffer->bind();
            vertexBuffer->updateData(vertices, sizeof(float) * 6 * 5);
            Render::getRender()->drawArrays(*vertexArray, *textShader, 6);
            x += (ch.advance >> 6) * scale;
        }
        vertexArray->unbind();
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}