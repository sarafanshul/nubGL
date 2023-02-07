//
// Created by Anshul Saraf on 23/10/22.
//

#ifndef OPENGLBASICS_TEST_H
#define OPENGLBASICS_TEST_H

#include "Shader.h"
#include "VertexArray.h"
#include "Texture.h"
#include "Common.h"
#include "Renderer.h"

namespace Test {

#define TEST_RETURN bool
#define TEST_RETURN_SUCCESS 1
#define TEST_RETURN_FAILURE 0

    class Test{
    public:
        Test() = default;
        virtual ~Test() = default;

        virtual TEST_RETURN OnUpdate( float  deltaTime ) = 0;
        virtual TEST_RETURN OnRender() = 0;
        virtual TEST_RETURN OnImGuiRender() = 0;

        float m_windowWidth = -1, m_windowHeight = -1;
    };
}

#endif //OPENGLBASICS_TEST_H
