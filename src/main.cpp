#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Shader.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "GLError.h"

/**
 * drawing a quadrilateral using index buffer.
 *             4         3
 *             ________
 *            |\      |
 *           |  \.   |
 *          |    \  |
 *         |______\|
 *         1       2
 *
 */
GLfloat vertices[] ={
        //   x         y       z             r         g         b         a
        -0.5, -0.5, 0.0,    0.3f, 0.3f, 0.7f, 0.5f,     // bottom left
        0.5, -0.5, 0.0,    0.8f, 0.3f, 0.2f, 0.5f,   // bottom right
        0.5, 0.5, 0.0,   0.9f, 0.0f, 0.0f, 0.5f,  // top right
        -0.5, 0.5, 0.0,  0.8f, 0.3f, 0.2f, 1.0f, // top left
};

GLuint indices[] = {
        0, 1, 3,
        1, 3, 2
};

int main() {

    // Initialize GLFW
    glfwInit();

    // Tell GLFW what version of OpenGL we are using
    // In this case we are using OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Tell GLFW we are using the CORE profile
    // So that means we only have the modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFW window object of 800 by 800 pixels, naming it "TestOpenGL"
    GLFWwindow *window = glfwCreateWindow(800, 800, "TestOpenGL", nullptr, nullptr);

    // Error check if the window fails to create
    if (!window) {
        std::cout << "Unable to create window :(\n";
        glfwTerminate();
        return -1;
    }

    // Introduce the window into the current context
    glfwMakeContextCurrent(window);

    // Load GLAD so it configures OpenGL
    if (!gladLoadGL()) {
        std::cerr << "Failed to initialize library loader " << std::endl;
    }

    // Specify the viewport of OpenGL in the Window
    // In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
//    glViewport(0, 0, 800, 800); // uncomment if output distorted.
    { // different scope for our opengl objects
        // Generates Shader object using shaders default.vert and default.frag
        Shader shaderProgram = Shader("Shaders/default.vert", "Shaders/default.frag");

        // Generates Vertex Array/Attribute Object and binds it
        VAO vao = VAO();
        vao.Bind();

        // Generates Vertex Buffer Object and links it to vertices
        VBO vbo = VBO(vertices, sizeof(vertices));

        // Generates Element Buffer Object and links it to indices
        EBO ebo = EBO(indices, sizeof(indices));

        // Links VBO to VAO
        vao.LinkVBO(vbo, 0, 3, GL_FLOAT, 7 * sizeof(float), (void *) 0); // aPos
        vao.LinkVBO(vbo, 1, 4, GL_FLOAT, 7 * sizeof(float), (void *) (3 * sizeof(float))); // aColor.

        // Unbind all to prevent accidentally modifying them
        vao.Unbind();
        vbo.Unbind();
        ebo.Unbind();

        // poll window
        while (!glfwWindowShouldClose(window)) {

            // Specify the color of the background
            GLCall(glClearColor(0.3f, 0.9f, 0.13f, 0.13f));
            // Clean the back buffer and assign the new color to it
            GLCall(glClear(GL_COLOR_BUFFER_BIT));
            // Tell OpenGL which Shader Program we want to use
            shaderProgram.Activate();

            // Assigns a value to the uniform; NOTE: Must always be done after activating the Shader Program
            shaderProgram.setFloat("scale", 1.0f);

            // Bind the VAO so OpenGL knows to use it
            vao.Bind();

            // Draw primitives, number of indices, datatype of indices, index of indices
            GLCall(glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, nullptr));

            // Swap the back buffer with the front buffer
            glfwSwapBuffers(window);
            // Take care of all GLFW events
            glfwPollEvents();
        }

        // Delete all the objects we've created
        vao.Delete();
        vbo.Delete();
        ebo.Delete();
        shaderProgram.Delete();
    }
    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program
    glfwTerminate();
    return 0;
}
