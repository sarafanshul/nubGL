#include <iostream>
#include "cmath"
#include <glad/glad.h>
#include "GLFW/glfw3.h"

const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
void main(){
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)";

const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
void main(){
    FragColor = vec4(0.8f, 0.3f, 0.2f, 1.0f);
}
)";

int main() {

    // init GLFW
    glfwInit();

    // specify version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create window
    GLFWwindow* window = glfwCreateWindow(800, 800, "test window", nullptr, nullptr);

    if(!window){
        std::cout << "Unable to create window :(\n";
        glfwTerminate();
        return -1;
    }

    // make window current
    glfwMakeContextCurrent(window);

    // load glad so it configures opengl
    gladLoadGL();

    // specify viewport
    glViewport(0, 0, 800, 800);

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
            -0.5, -0.5, 0.0, // bottom left
            0.5, -0.5, 0.0, // bottom right
            0.5, 0.5, 0.0,  // top right
            -0.5, 0.5, 0.0 // top left
    };

    GLuint indices[] = {
            0, 1, 3,
            1, 3, 2
    };

    // create shader and attach source -> compile shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // create shader program and attach shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);


    // VBO
    GLuint VBO[1], VAO[1], EBO[1];
    glGenVertexArrays(1, VAO); // before VBO
    glGenBuffers(1, VBO);
    glGenBuffers(1, EBO);

    glBindVertexArray(VAO[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // tells how to read vertex data.
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)nullptr );
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // ordering is imp.
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // unbind after VAO


    // poll window
    while( !glfwWindowShouldClose(window) ){

        glClearColor(0.3f, 0.9f, 0.13f, 0.13f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);

        glBindVertexArray(VAO[0]);
        glPointSize( 20.0 ); // for drawing points
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    // delete redundant obj
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteVertexArrays(1, VAO);
    glDeleteBuffers(1, VBO);
    glDeleteBuffers(1, EBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
