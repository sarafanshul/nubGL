//
// Created by Anshul Saraf on 23/10/22.
//

#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "GLBufferLayout.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "tests/Tests.h"
#include "Instrumentor.h"

int main() {
    glfwInit();

    const char* glsl_version = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    HZ_PROFILE_BEGIN_SESSION("Runtime", "HazelProfile-Runtime.json");

    const int w_Width = 16 * 50  , w_Height = 12 * 50 ;
    GLFWwindow* window = glfwCreateWindow(w_Width, w_Height, "TestOpenGL", nullptr, nullptr);
    if ( !window ) {
        std::cout << "Unable to create window :(\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if ( !gladLoadGL()) {
        std::cerr << "Failed to initialize library loader " << std::endl;
    }

    { // different scope for our opengl objects

        GLCall( glEnable(GL_BLEND) );
        GLCall( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );

        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);

        Test::TestBatchRenderingV2 test ;
        test.m_windowWidth = w_Width, test.m_windowHeight = w_Height;

        while (!glfwWindowShouldClose(window)) {

            test.OnUpdate(0.0f) ;
            test.OnRender() ;

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            test.OnImGuiRender() ;

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

    }

    glfwDestroyWindow(window);

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    glfwTerminate();

    HZ_PROFILE_END_SESSION();
    return 0;
}
