//
// Created by Anshul Saraf on 26/02/23.
//

#ifndef OPENGLBASICS_TESTDEBUGLAYER_H
#define OPENGLBASICS_TESTDEBUGLAYER_H

#include "Test.h"
#include "imgui.h"
#include "Instrumentor.h"

namespace Test {

    class TestDebugLayer : public Test {
    public:

        bool OnUpdate(float deltaTime) override {
            return TEST_RETURN_FAILURE;
        }

        inline bool OnRender() override {
            return TEST_RETURN_FAILURE;
        }

        bool OnImGuiRender() override {
            ImGuiWindowFlags window_flags = 0;
            window_flags |= ImGuiWindowFlags_NoBackground;
            window_flags |= ImGuiWindowFlags_NoTitleBar;
            window_flags |= ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoResize;
            bool *open_ptr = nullptr;
            ImGui::Begin("debug", open_ptr, window_flags);
            ImGui::SetWindowPos(ImVec2(0,0),0);
            ImGui::Text("%12f FPS", ImGui::GetIO().Framerate);
            ImGui::End();
            return TEST_RETURN_SUCCESS;
        }
    };
}

#endif //OPENGLBASICS_TESTDEBUGLAYER_H
