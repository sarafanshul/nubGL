//
// Created by Anshul Saraf on 21/02/23.
//

#ifndef OPENGLBASICS_TESTBATCHRENDERINGV2_H
#define OPENGLBASICS_TESTBATCHRENDERINGV2_H


#include <map>
#include <array>
#include "TestDebugLayer.h"
#include "glm/glm.hpp"
#include "spdlog/spdlog.h"

struct Vertex{
    glm::vec3 m_Pos;
    glm::vec4 m_Col;
    glm::vec2 m_TexCord ;
    float m_TexId;
};

struct Quad{
    std::array<Vertex, 4> vertices;
    std::array<uint, 6> indices;
};

namespace Test {

    /**
     * Needs an Dynamic VBO for usage
     * since we are storing all data in VBO instead of uniforms.
     *
     * for textures we use a texture map and pass an texture index to use for.
     */
    class TestBatchRenderingV2 : public TestDebugLayer {
    public:
        TestBatchRenderingV2() ;
        ~TestBatchRenderingV2() override ;

        TEST_RETURN OnUpdate( float  deltaTime ) override;
        TEST_RETURN OnRender() override;
        TEST_RETURN OnImGuiRender() override;

    private:
        Scope<Shader> shader ;
        Scope<VertexArray> vao ;
        Scope<VertexBuffer> vbo ;
        Scope<IndexBuffer> ebo ;
        Scope<Renderer> renderer ;

        std::string vert_shader = "Shaders/test_BRV2.vert" ;
        std::string frag_shader = "Shaders/test_BRV2.frag" ;

        std::map<int, Scope<Texture2D>> textureMap;

        float m_Vertices[1000];
        uint m_Indices[1000];
        std::vector<Quad> m_Quads;
        uint quadsToDraw;

        float rot = 0 ;
    };

}


#endif //OPENGLBASICS_TESTBATCHRENDERINGV2_H
