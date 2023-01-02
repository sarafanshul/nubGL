//
// Created by Anshul Saraf on 17/11/22.
//

#include "../TestEBO.h"
#include "imgui.h"


Test::TestEBO::TestEBO() {

    float vertices[] = {
      -0.5, -0.5, 0.0, // left bottom
       0.5, -0.5, 0.0, // right bottom
      -0.5,  0.5, 0.0, // left top
       0.5,  0.5, 0.0, // right top
    };

    uint indices[] = {
        0, 1, 2, // triangle 1
        1, 3, 2, // triangle 2
    };

    shaderProgram = CreateScope<Shader>(vert_shader_path.c_str(), frag_shader_path.c_str());
    vertexArray = CreateScope<VertexArray>();

    vertexArray->Bind();

    vertexBuffer = CreateScope<VertexBuffer>(vertices, sizeof(vertices));
    indexBuffer = CreateScope<IndexBuffer>(indices, sizeof(indices));

    GLBufferLayout layout;
    layout.Push<float>(3);

    vertexArray->AddBuffer(*vertexBuffer, layout);

    vertexArray->Unbind();
    vertexBuffer->Unbind();
    indexBuffer->Unbind();
    shaderProgram->Unbind();

    renderer = CreateScope<Renderer>() ;
}

Test::TestEBO::~TestEBO() {
    vertexArray->Delete();
    vertexArray.reset();

    vertexBuffer->Delete();
    vertexBuffer.reset();

    indexBuffer->Delete();
    indexBuffer.reset();

    shaderProgram->Delete();
    shaderProgram.reset();

    renderer.reset();
}

TEST_RETURN Test::TestEBO::OnUpdate(float deltaTime) {
    return TEST_RETURN_FAILURE;
}

TEST_RETURN Test::TestEBO::OnRender() {
    GLCall(glClearColor(0.5f, 0.7f, 0.7f, 0.13f));

    renderer->Clear() ;

    shaderProgram->Bind();
    shaderProgram->setFloat4("iColor", m_Color[0], m_Color[1], m_Color[2], m_Color[3]);

    renderer->DrawElements(*vertexArray, *indexBuffer, *shaderProgram );

    return TEST_RETURN_SUCCESS;
}

TEST_RETURN Test::TestEBO::OnImGuiRender() {
    ImGui::ColorEdit4("Quad Color", m_Color);
    return TEST_RETURN_SUCCESS;
}

