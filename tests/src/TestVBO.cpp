//
// Created by Anshul Saraf on 23/10/22.
//

#include "../TestVBO.h"
#include "imgui.h"

Test::TestVBO::TestVBO() :
        m_Color{0.2, 0.3, 0.8, 0.9} {
    float vertices[] = {
        -0.5, -0.5, 0.0, // bottom left
        0.5, -0.5, 0.0, // bottom right
        0.0,  0.5, 0.0, // top center
    };

    shaderProgram = CreateScope<Shader>("Shaders/test_vbo.vert", "Shaders/test_vbo.frag");
    vertexArray = CreateScope<VertexArray>() ;

    vertexArray->Bind();

    vertexBuffer = CreateScope<VertexBuffer>(vertices, sizeof(vertices));

    GLBufferLayout layout;
    layout.Push<float>(3) ; // x,y,z;

    vertexArray->AddBuffer(*vertexBuffer, layout);

    vertexArray->Unbind();
    vertexBuffer->Unbind();
    shaderProgram->Unbind();

    renderer = CreateScope<Renderer>() ;

}

Test::TestVBO::~TestVBO() {

    vertexArray->Delete();
    vertexArray.reset();

    vertexBuffer->Delete();
    vertexBuffer.reset();

    shaderProgram->Delete();
    shaderProgram.reset();

    renderer.reset();
}

TEST_RETURN Test::TestVBO::OnUpdate(float deltaTime) {
    return TEST_RETURN_FAILURE;
}

TEST_RETURN Test::TestVBO::OnRender() {

    GLCall(glClearColor(0.5f, 0.7f, 0.7f, 0.13f));

    renderer->Clear() ;

    shaderProgram->Bind() ;
    vertexArray->Bind() ;

    shaderProgram->setFloat4("iColor", m_Color[0], m_Color[1], m_Color[2], m_Color[3]);

    GLCall( glDrawArrays(GL_TRIANGLES, 0, 9) );

    return TEST_RETURN_SUCCESS;
}

TEST_RETURN Test::TestVBO::OnImGuiRender() {
    ImGui::ColorEdit4("Quad Color", m_Color);
    return TEST_RETURN_SUCCESS;
}
