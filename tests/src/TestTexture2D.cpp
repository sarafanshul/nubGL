//
// Created by Anshul Saraf on 03/01/23.
//


#include "../TestTexture2D.h"
#include "imgui.h"


Test::TestTexture2D::TestTexture2D() {

    GLfloat vertices[] = {
//            x      y     z        t_x   t_y
            -0.5,  -0.5,  0.0,     0.0f,  0.0f,    // bottom left
             0.5,  -0.5,  0.0,     1.0f,  0.0f,    // bottom right
             0.5,   0.5,  0.0,     1.0f,  1.0f,    // top right
            -0.5,   0.5,  0.0,     0.0f,  1.0f,    // top left
    };

    uint indices[] = {
            0, 1, 3, // triangle 1
            1, 3, 2, // triangle 2
    };

    shaderProgram = CreateScope<Shader>(vert_shader_path.c_str(), frag_shader_path.c_str()) ;

    // set blinding params
    GLCall( glEnable(GL_BLEND) );
    GLCall( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );

    vertexArray = CreateScope<VertexArray>();
    vertexArray->Bind();

    vertexBuffer = CreateScope<VertexBuffer>(vertices, sizeof(vertices));
    indexBuffer = CreateScope<IndexBuffer>(indices, sizeof(indices)) ;

    GLBufferLayout layout;
    layout.Push<float>(3); //aPos
    layout.Push<float>(2); // u_Texture coords

    vertexArray->AddBuffer(*vertexBuffer, layout);


    texture0 = CreateScope<Texture>(texture_path);

    shaderProgram->Bind();
    texture0->Bind(slot0);
    shaderProgram->setInt("u_Texture0", slot0);

    vertexArray->Unbind();
    vertexBuffer->Unbind();
    indexBuffer->Unbind();
    texture0->Unbind();
    shaderProgram->Unbind();

    renderer = CreateScope<Renderer>() ;
}

Test::TestTexture2D::~TestTexture2D() {
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

TEST_RETURN Test::TestTexture2D::OnUpdate(float deltaTime) {
    return TEST_RETURN_FAILURE;
}

TEST_RETURN Test::TestTexture2D::OnRender() {
    GLCall(glClearColor(0.5f, 0.7f, 0.7f, 0.13f));

    renderer->Clear() ;

    shaderProgram->Bind();
    texture0->Bind(slot0);

    renderer->DrawElements(*vertexArray, *indexBuffer, *shaderProgram);

    return TEST_RETURN_SUCCESS;
}

TEST_RETURN Test::TestTexture2D::OnImGuiRender() {
    return TEST_RETURN_FAILURE;
}
