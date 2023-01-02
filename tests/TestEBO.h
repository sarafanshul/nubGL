//
// Created by Anshul Saraf on 17/11/22.
//

#ifndef OPENGLBASICS_TESTEBO_H
#define OPENGLBASICS_TESTEBO_H

#include "Test.h"
#include "Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Common.h"
#include "Renderer.h"

namespace Test {
    class TestEBO : public Test{
    public:

        TestEBO();

        ~TestEBO() override;

        TEST_RETURN OnUpdate(float deltaTime) override;

        TEST_RETURN OnRender() override;

        TEST_RETURN OnImGuiRender() override;
    private:

        Scope<Shader> shaderProgram;
        Scope<VertexArray> vertexArray;
        Scope<VertexBuffer> vertexBuffer;
        Scope<IndexBuffer> indexBuffer;
        Scope<Renderer> renderer ;
        const std::string vert_shader_path = "Shaders/test_ebo.vert";
        const std::string frag_shader_path = "Shaders/test_ebo.frag";
        float m_Color[4];
    };
}

#endif //OPENGLBASICS_TESTEBO_H
