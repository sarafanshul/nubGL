//
// Created by Anshul Saraf on 21/02/23.
//

#include "../TestBatchRenderingV2.h"
#include "glm/ext/matrix_transform.hpp"
#include "Logger.h"
#include <glm/gtx/rotate_vector.hpp>


std::vector<Quad> convert(const float* vertices, int size, int offset ){
    std::vector<Quad> ret(3) ;

    int idx = 0 ;
    for(int i = 0 ; i < size ; i += offset){
        Vertex v = Vertex();
        v.m_Pos[0] = vertices[i + 0];
        v.m_Pos[1] = vertices[i + 1];
        v.m_Pos[2] = vertices[i + 2];

        v.m_Col[0] = vertices[i + 3];
        v.m_Col[1] = vertices[i + 4];
        v.m_Col[2] = vertices[i + 5];
        v.m_Col[3] = vertices[i + 6];

        v.m_TexCord[0] = vertices[ i + 7];
        v.m_TexCord[1] = vertices[ i + 8];

        v.m_TexId = vertices[i + 9];

        ret[idx / 4].vertices[idx % 4] = v;
        idx++ ;
    }
    return ret ;
}

void convert(const std::vector<Quad>& quads, float* ret){
    int i = 0;
    for(const auto q: quads){
        for(const auto v : q.vertices) {
            ret[ i++ ] = v.m_Pos[ 0 ];
            ret[ i++ ] = v.m_Pos[ 1 ];
            ret[ i++ ] = v.m_Pos[ 2 ];
            ret[ i++ ] = v.m_Col[ 0 ];
            ret[ i++ ] = v.m_Col[ 1 ];
            ret[ i++ ] = v.m_Col[ 2 ];
            ret[ i++ ] = v.m_Col[ 3 ];
            ret[ i++ ] = v.m_TexCord[ 0 ];
            ret[ i++ ] = v.m_TexCord[ 1 ];
            ret[ i++ ] = v.m_TexId;
        }
    }
}

Test::TestBatchRenderingV2::TestBatchRenderingV2() : TestDebugLayer() {
    HZ_PROFILE_FUNCTION();

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

    m_Quads = convert(vertices, sizeof(vertices) / sizeof(float ), 3 + 4 + 2 + 1);

    std::vector<std::string> mTextureAssets = {
            "Textures/rock_wall_06_diff_1k.jpg",
            "Textures/fabric_pattern_07_col_1_1k.png",
            "Textures/brick_wall_001_diffuse_1k.jpg"
    };

    shader = CreateScope<Shader>(vert_shader, frag_shader);
    vao = CreateScope<VertexArray>();

    vao->Bind();

    vbo = CreateScope<VertexBuffer>(nullptr, sizeof(Vertex) * 1000, GL_DYNAMIC_DRAW);
    ebo = CreateScope<IndexBuffer>(indices, sizeof(indices));

    GLBufferLayout layout;
    layout.Push<float>(sizeof(Vertex::m_Pos) / sizeof(float)); // pos
    layout.Push<float>(sizeof(Vertex::m_Col) / sizeof(float)); // color
    layout.Push<float>(sizeof(Vertex::m_TexCord) / sizeof(float)); // texCords
    layout.Push<float>(sizeof(Vertex::m_TexId) / sizeof(float)); // texId

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

Test::TestBatchRenderingV2::~TestBatchRenderingV2() {
    vao->Unbind();
    vbo->Unbind();
    ebo->Unbind();
    shader->Unbind();

    vao->Delete();
    vbo->Delete();
    ebo->Delete();
    shader->Delete();

//    TestDebugLayer::~TestDebugLayer();
}

TEST_RETURN Test::TestBatchRenderingV2::OnUpdate( float  deltaTime ) {
    TestDebugLayer::OnUpdate(deltaTime);
    return TEST_RETURN_FAILURE;
}

TEST_RETURN Test::TestBatchRenderingV2::OnRender() {
    TestDebugLayer::OnRender();

    HZ_PROFILE_FUNCTION();

    renderer->Clear();
    glClearColor(0.3, 0.4, 0.5, 0.9);

    // do some ops here
    for ( auto& v : m_Quads[0].vertices){
        glm::mat4 rotationMat(1);
        v.m_Pos = glm::rotate(v.m_Pos, 0.01f, glm::vec3(0.0f, 0.0f, 1.0f));
    }
    convert(m_Quads, m_Vertices);

    shader->Bind();

    vao->Bind();
    // set data for vbo every frame.
    vbo->SetBufferSubData(m_Vertices, (GLsizeiptr)(m_Quads.size() * 4 * sizeof(Vertex)) );

    for(const auto& [idx, tex] : textureMap){
        tex->Bind(idx);
    }

    renderer->DrawElements(*vao, *ebo, *shader);

    return TEST_RETURN_SUCCESS;
}

TEST_RETURN Test::TestBatchRenderingV2::OnImGuiRender() {
    TestDebugLayer::OnImGuiRender();
    return TEST_RETURN_FAILURE;
}
