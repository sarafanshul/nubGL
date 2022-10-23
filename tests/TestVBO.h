//
// Created by Anshul Saraf on 23/10/22.
//

#ifndef OPENGLBASICS_TESTVBO_H
#define OPENGLBASICS_TESTVBO_H

#include "Test.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Utils.h"
#include "Renderer.h"

namespace Test {
    class TestVBO : public Test {
    public:

        TestVBO();

        ~TestVBO() override;

        TEST_RETURN OnUpdate(float deltaTime) override;

        TEST_RETURN OnRender() override;

        TEST_RETURN OnImGuiRender() override;

    private:
        Scope<Renderer> renderer;
        Scope<Shader> shaderProgram ;
        Scope<VertexArray> vertexArray ;
        Scope<VertexBuffer> vertexBuffer ;
    };
}


#endif //OPENGLBASICS_TESTVBO_H
