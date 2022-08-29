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
    GLFWwindow* window = glfwCreateWindow(800, 800, "TestOpenGL", nullptr, nullptr);

    // Error check if the window fails to create
    if(!window){
        std::cout << "Unable to create window :(\n";
        glfwTerminate();
        return -1;
    }

    // Introduce the window into the current context
    glfwMakeContextCurrent(window);

    // Load GLAD so it configures OpenGL
    gladLoadGL();

    // Specify the viewport of OpenGL in the Window
    // In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
    glViewport(0, 0, 800, 800);

    // Create Vertex Shader Object and get its reference
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Attach Vertex Shader source to the Vertex Shader Object
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    // Compile the Vertex Shader into machine code
    glCompileShader(vertexShader);


    // Create Fragment Shader Object and get its reference
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Attach Fragment Shader source to the Fragment Shader Object
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    // Compile the Vertex Shader into machine code
    glCompileShader(fragmentShader);


    // Create Shader Program Object and get its reference
    GLuint shaderProgram = glCreateProgram();
    // Attach the Vertex and Fragment Shaders to the Shader Program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // Wrap-up/Link all the shaders together into the Shader Program
    glLinkProgram(shaderProgram);



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


    // Create reference containers for the Vertex Array Object, the Vertex Buffer Object, and the Element Buffer Object
    GLuint VBO[1], VAO[1], EBO[1];
    // Generate the VAO, VBO, and EBO with only 1 object each
    glGenVertexArrays(1, VAO); // before VBO
    glGenBuffers(1, VBO);
    glGenBuffers(1, EBO);

    // Make the VAO the current Vertex Array Object by binding it
    glBindVertexArray(VAO[0]);

    // Bind the VBO specifying it's a GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    // Introduce the vertices into the VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind the EBO specifying it's a GL_ELEMENT_ARRAY_BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    // Introduce the indices into the EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Configure the Vertex Attribute so that OpenGL knows how to read the VBO
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)nullptr );
    // Enable the Vertex Attribute so that OpenGL knows to use it
    glEnableVertexAttribArray(0);

    // Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
    glBindBuffer(GL_ARRAY_BUFFER, 0); // ordering is imp.
    glBindVertexArray(0);
    // Bind the EBO to 0 so that we don't accidentally modify it
    // MAKE SURE TO UNBIND IT AFTER UNBINDING THE VAO, as the EBO is linked in the VAO
    // This does not apply to the VBO because the VBO is already linked to the VAO during glVertexAttribPointer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // unbind after VAO


    // poll window
    while( !glfwWindowShouldClose(window) ){

        // Specify the color of the background
        glClearColor(0.3f, 0.9f, 0.13f, 0.13f);
        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT);
        // Tell OpenGL which Shader Program we want to use
        glUseProgram(shaderProgram);

        // Bind the VAO so OpenGL knows to use it
        glBindVertexArray(VAO[0]);

        // Draw primitives, number of indices, datatype of indices, index of indices
        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, nullptr);

        // Swap the back buffer with the front buffer
        glfwSwapBuffers(window);
        // Take care of all GLFW events
        glfwPollEvents();
    }

    // Delete all the objects we've created
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteVertexArrays(1, VAO);
    glDeleteBuffers(1, VBO);
    glDeleteBuffers(1, EBO);
    glDeleteProgram(shaderProgram);

    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program
    glfwTerminate();
    return 0;
}
