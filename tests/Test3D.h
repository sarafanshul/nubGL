//
// Created by Anshul Saraf on 07/02/23.
//

#ifndef OPENGLBASICS_TEST3D_H
#define OPENGLBASICS_TEST3D_H

#include "Test.h"
#include "glm/glm.hpp"

namespace Test {

    /**
     * Uses MVP matrix for 3D
     */
    class Test3D : public Test {

    public:
        Test3D() ;
        ~Test3D() override ;

        TEST_RETURN OnUpdate( float  deltaTime ) override;
        TEST_RETURN OnRender() override;
        TEST_RETURN OnImGuiRender() override;

    private:
        glm::mat4 model, view, proj;
        Scope<Shader> shader ;
        Scope<VertexArray> vao ;
        Scope<VertexBuffer> vbo ;
        Scope<IndexBuffer> ebo ;
        Scope<Renderer> renderer ;
        Scope<Texture> texture0;

        std::string vert_shader = "Shaders/test_3D.vert" ;
        std::string frag_shader = "Shaders/test_3D.frag" ;
        std::string texture_path = "Textures/op.jpeg" ;

        float rot = 0 ;
    };

}

#endif //OPENGLBASICS_TEST3D_H
