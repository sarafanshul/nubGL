//
// Created by Anshul Saraf on 03/01/23.
//

#ifndef OPENGLBASICS_TESTTEXTURE2D_H
#define OPENGLBASICS_TESTTEXTURE2D_H

#include "Test.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Texture.h"
#include "Common.h"
#include "Renderer.h"

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

        Scope<Texture> texture0;
        int slot0 = 0;

        const std::string vert_shader_path = "Shaders/test_texture2D.vert";
        const std::string frag_shader_path = "Shaders/test_texture2D.frag";
        const std::string texture_path     = "Textures/alpha_image.png";
    };
}

#endif //OPENGLBASICS_TESTTEXTURE2D_H
