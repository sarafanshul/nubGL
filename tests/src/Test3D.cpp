//
// Created by Anshul Saraf on 07/02/23.
//
#include "../Test3D.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "Profiler.h"
#include "Logger.h"

Test::Test3D::Test3D() {

    float vertices3D[] = {
//            x    y     z        t_x
            -0.5, 0.0, 0.5, 0.0, 0.0,
            -0.5, 0.0, -0.5, 5.0, 0.0,
            0.5, 0.0, -0.5, 0.0, 0.0,
            0.5, 0.0, 0.5, 5.0, 0.0,
            0.0, 0.8, 0.0, 2.5, 5.0,
    };
    uint indices[] = {
            0, 1, 2,
            0, 2, 3,
            0, 1, 4,
            1, 2, 4,
            2, 3, 4,
            3, 0, 4,
    };

    // set blinding params
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    GLCall(glEnable(GL_DEPTH_TEST));


    shader = CreateScope<Shader>(vert_shader.c_str(), frag_shader.c_str());

    vao = CreateScope<VertexArray>();
    vao->Bind();

    vbo = CreateScope<VertexBuffer>(vertices3D, sizeof(vertices3D));
    ebo = CreateScope<IndexBuffer>(indices, sizeof(indices));

    GLBufferLayout layout;
    layout.Push<float>(3); // aPos
    layout.Push<float>(2); // texCoord

    vao->AddBuffer(*vbo, layout);

    texture0 = CreateScope<Texture>(texture_path);

    shader->Bind();
    texture0->Bind(0);
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT)); // repeat wrap the texture
    shader->setInt("u_Texture0", 0);

    vao->Unbind();
    vbo->Unbind();
    ebo->Unbind();
    texture0->Unbind();
    shader->Unbind();

    model = glm::mat4(1.0);
    view = glm::mat4(1.0);
    proj = glm::mat4(1.0); // refer cherno

}

Test::Test3D::~Test3D() {
    vao->Unbind();
    vbo->Unbind();
    ebo->Unbind();
    texture0->Unbind();
    shader->Unbind();

    vao->Delete();
    vbo->Delete();
    ebo->Delete();
    shader->Delete();

    if ( Profiler::m_PerformanceProfile ) {
        const auto& perFrameData = Profiler::m_PerformanceProfile->GetPerFrameData();
        TRACE("-----------Performance-----------------");
        for (auto&& [name, time]: perFrameData) {
            INFO("{0}: {1}ms", name, time);
        }
        TRACE("---------------------------------------");
        Profiler::m_PerformanceProfile->Clear();
    }
}

bool Test::Test3D::OnUpdate(float deltaTime) {
    return false;
}

bool Test::Test3D::OnRender() {
    PROFILE("OnRender");
    model = glm::rotate(glm::mat4(1.0), glm::radians(rot), glm::vec3(0.0, 0.1, 0.0));
    view = glm::translate(glm::mat4(1.0), glm::vec3(0.0f, -0.5f, -2.0f));
    proj = glm::perspective(glm::radians(45.0f), (m_windowWidth / m_windowHeight), 0.1f, 100.0f);

    renderer->Clear();

    shader->Bind();
    texture0->Bind(0);

    shader->setUniformMat4f("model", model);
    shader->setUniformMat4f("view", view);
    shader->setUniformMat4f("proj", proj);

    renderer->DrawElements(*vao, *ebo, *shader);

    rot += 0.1;

    return TEST_RETURN_SUCCESS;
}

bool Test::Test3D::OnImGuiRender() {
    return false;
}

