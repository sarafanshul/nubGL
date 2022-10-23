//
// Created by Anshul Saraf on 23/10/22.
//

#include "../TestClearColor.h"
#include "Renderer.h"

#include "imgui.h"

Test::TestClearColor::TestClearColor() :
        m_ClearColor{0.2, 0.3, 0.8, 0.9}{}

Test::TestClearColor::~TestClearColor() = default;

TEST_RETURN Test::TestClearColor::OnUpdate(float deltaTime) {
    return false;
}

TEST_RETURN Test::TestClearColor::OnRender() {

    GLCall( glClearColor( m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3] ) ) ;
    GLCall( glClear( GL_COLOR_BUFFER_BIT ) ) ;

    return TEST_RETURN_SUCCESS ;
}

TEST_RETURN Test::TestClearColor::OnImGuiRender() {

    ImGui::ColorEdit4("Clear Color", m_ClearColor);

    return TEST_RETURN_SUCCESS ;
}
