//
// Created by Anshul Saraf on 21/02/23.
//

#include "../TestBatchRenderingV1.h"

Test::TestBatchRenderingV1::TestBatchRenderingV1() {

    float vertices[] = {
            // x , y , z       r,  g,    b,   a,     tx ,ty,   tid
            // first square
            0.8, 0.2, 0.0,    0.3, 0.4, 0.5, 0.9,   1.0, 0.0,    0,
            0.2, 0.2, 0.0,    0.3, 0.4, 0.5, 0.9,   0.0, 0.0,    0,
            0.2, 0.8, 0.0,    0.3, 0.4, 0.5, 0.9,   0.0, 1.0,    0,
            0.8, 0.8, 0.0,    0.3, 0.4, 0.5, 0.9,   1.0, 1.0,    0,

            // second square
            -0.8, -0.2, 0.0,  0.7, 0.8, 0.1, 0.9,   0.0, 1.0,    1,
            -0.2, -0.2, 0.0,  0.7, 0.8, 0.1, 0.9,   1.0, 1.0,    1,
            -0.2, -0.8, 0.0,  0.7, 0.8, 0.1, 0.9,   1.0, 0.0,    1,
            -0.8, -0.8, 0.0,  0.7, 0.8, 0.1, 0.9,   0.0, 0.0,    1,

            // third square
            0.8, -0.2, 0.0,   0.1, 0.8, 0.1, 0.9,   1.0, 1.0,    2,
            0.2, -0.2, 0.0,   0.1, 0.8, 0.1, 0.9,   0.0, 1.0,    2,
            0.2, -0.8, 0.0,   0.1, 0.8, 0.1, 0.9,   0.0, 0.0,    2,
            0.8, -0.8, 0.0,   0.1, 0.8, 0.1, 0.9,   1.0, 0.0,    2,
    };

    uint indices[] = {
            // first
            0, 1, 2,
            0, 2, 3,

            // second
            4, 5, 6,
            4, 6, 7,

            // third
            8, 9, 10,
            8, 10, 11,
    };

    std::vector<std::string> mTextureAssets = {
            "Textures/rock_wall_06_diff_1k.jpg",
            "Textures/fabric_pattern_07_col_1_1k.png",
            "Textures/brick_wall_001_diffuse_1k.jpg"
    };

    shader = CreateScope<Shader>(vert_shader, frag_shader);
    vao = CreateScope<VertexArray>();

    vao->Bind();

    vbo = CreateScope<VertexBuffer>(vertices, sizeof(vertices));
    ebo = CreateScope<IndexBuffer>(indices, sizeof(indices));

    GLBufferLayout layout;
    layout.Push<float>(3); // pos
    layout.Push<float>(4); // color
    layout.Push<float>(2); // texCords
    layout.Push<float>(1); // texId

    vao->AddBuffer(*vbo, layout);

    shader->Bind();
    for(int i = 0 ; i < mTextureAssets.size() ; i++){
        textureMap[i] = CreateScope<Texture>(mTextureAssets[i]);
    }

    auto loc = glGetUniformLocation(shader->GetId(),"mTextures");
    int samplers[3] = {0, 1, 2};
    glUniform1iv(loc, 3, samplers);

    vao->Unbind();
    vbo->Unbind();
    ebo->Unbind();
    shader->Unbind();

    renderer = CreateScope<Renderer>();

}

Test::TestBatchRenderingV1::~TestBatchRenderingV1() {
    vao->Unbind();
    vbo->Unbind();
    ebo->Unbind();
    shader->Unbind();

    vao->Delete();
    vbo->Delete();
    ebo->Delete();
    shader->Delete();
}

TEST_RETURN Test::TestBatchRenderingV1::OnUpdate( float  deltaTime ) {
    return TEST_RETURN_FAILURE;
}

TEST_RETURN Test::TestBatchRenderingV1::OnRender() {
    renderer->Clear();

    shader->Bind();

    for(const auto& [idx, tex] : textureMap){
        tex->Bind(idx);
    }

//    auto loc = glGetUniformLocation(shader->GetId(),"mTextures");
//    int samplers[3] = {0, 1, 2};
//    glUniform1iv(loc, 3, samplers);

    renderer->DrawElements(*vao, *ebo, *shader);

    return TEST_RETURN_SUCCESS;
}

TEST_RETURN Test::TestBatchRenderingV1::OnImGuiRender() {
    return TEST_RETURN_FAILURE;
}
