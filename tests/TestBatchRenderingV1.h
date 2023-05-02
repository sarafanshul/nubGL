//
// Created by Anshul Saraf on 21/02/23.
//

#ifndef OPENGLBASICS_TESTBATCHRENDERINGV1_H
#define OPENGLBASICS_TESTBATCHRENDERINGV1_H

#include <map>
#include "Test.h"
#include "glm/glm.hpp"
#include "spdlog/spdlog.h"

namespace Test {

    /**
     * Needs an Dynamic VBO for usage
     * since we are storing all data in VBO instead of uniforms.
     *
     * for textures we use a texture map and pass an texture index to use for.
     */
    class TestBatchRenderingV1 : public Test {
    public:
        TestBatchRenderingV1() ;
        ~TestBatchRenderingV1() override ;

        TEST_RETURN OnUpdate( float  deltaTime ) override;
        TEST_RETURN OnRender() override;
        TEST_RETURN OnImGuiRender() override;

    private:
        Scope<Shader> shader ;
        Scope<VertexArray> vao ;
        Scope<VertexBuffer> vbo ;
        Scope<IndexBuffer> ebo ;
        Scope<Renderer> renderer ;

        std::string vert_shader = "Shaders/test_BRV1.vert" ;
        std::string frag_shader = "Shaders/test_BRV1.frag" ;
        std::string texture_path = "Textures/op.jpeg" ;

        std::map<int, Scope<Texture2D>> textureMap;

        float rot = 0 ;
    };

}


#endif //OPENGLBASICS_TESTBATCHRENDERINGV1_H
