//
// Created by Anshul Saraf on 03/01/23.
//

#ifndef OPENGLBASICS_TESTTEXTURE2D_H
#define OPENGLBASICS_TESTTEXTURE2D_H

#include "Test.h"
#include "TextureConverter.h"

#define COPY_TEXTURE 0 // copy the data from texture0 to texture1 and then render.
#define TEXTURE_CONVERTER 1

namespace Test{
    class TestTexture2D : public Test {
    public:

        TestTexture2D() ;

        ~TestTexture2D() override;

        TEST_RETURN OnUpdate(float deltaTime) override;

        TEST_RETURN OnRender() override;

        TEST_RETURN OnImGuiRender() override;

    private:
        Scope<Shader> shaderProgram;
        Scope<VertexArray> vertexArray;
        Scope<VertexBuffer> vertexBuffer;
        Scope<IndexBuffer> indexBuffer;

        Scope<Renderer> renderer;

#if TEXTURE_CONVERTER
        Scope<TextureConverter> converter;
        Scope<Texture2D> renderTexture;
#endif
        Scope<Texture2D> texture0;
        int slot0 = 0;

        const std::string vert_shader_path = "Shaders/test_texture2D.vert";
        const std::string frag_shader_path = "Shaders/test_texture2D.frag";
        const std::string texture_path     = "Textures/alpha_image.png";

#if COPY_TEXTURE
        GLuint fbo;
        Scope<Texture2D> texture1;
        int slot1 = 1;
#endif
    };
}

#endif //OPENGLBASICS_TESTTEXTURE2D_H
