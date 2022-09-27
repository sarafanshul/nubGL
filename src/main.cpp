#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Renderer.h"
#include "GLBufferLayout.h"
#include "Texture.h"

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
GLfloat vertices[] = {
//        x      y     z        r      g      b     a        t_x   t_y
        -0.5,  -0.5,  0.0,    0.3f,  0.3f,  0.7f,  0.5f,    0.0f,  0.0f,    // bottom left
         0.5,  -0.5,  0.0,    0.8f,  0.3f,  0.2f,  0.5f,    1.0f,  0.0f,    // bottom right
         0.5,   0.5,  0.0,    0.9f,  0.0f,  0.0f,  0.5f,    1.0f,  1.0f,    // top right
        -0.5,   0.5,  0.0,    0.8f,  0.3f,  0.2f,  1.0f,    0.0f,  1.0f,    // top left
};
// Texture2D coordinates range from 0 to 1 in the x and y-axis

GLuint indices[] = {
        0, 1, 3, // first  triangle
        1, 3, 2 //  second triangle
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
    const int w_Width = 16 * 60  , w_Height = 9 * 60 ;
    GLFWwindow* window = glfwCreateWindow(w_Width, w_Height, "TestOpenGL", nullptr, nullptr);

    // Error check if the window fails to create
    if ( !window ) {
        std::cout << "Unable to create window :(\n";
        glfwTerminate();
        return -1;
    }

    // Introduce the window into the current context
    glfwMakeContextCurrent(window);

    // Load GLAD so it configures OpenGL
    if ( !gladLoadGL()) {
        std::cerr << "Failed to initialize library loader " << std::endl;
    }

    { // different scope for our opengl objects
        glm::mat4 proj = glm::ortho(-1.0f, 1.0f, -(float)w_Height/w_Width, (float)w_Height/w_Width, -1.0f, 1.0f); // 9 : 16 A_R
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)); // camera

        Shader shaderProgram = Shader("Shaders/default.vert", "Shaders/default.frag");

        // set blinding params
        GLCall( glEnable(GL_BLEND) );
        GLCall( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );

        // Generates Vertex Array/Attribute Object and binds it
        VertexArray vao = VertexArray();
        vao.Bind();

        // Generates Vertex GLBuffer Object and layouts
        VertexBuffer vbo = VertexBuffer(vertices, sizeof(vertices));
        GLBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(4);
        layout.Push<float>(2);

        // attach buffers to vao
        vao.AddBuffer(vbo, layout);

        // Generates Element GLBuffer Object and links it to indices
        IndexBuffer ebo = IndexBuffer(indices, sizeof(indices));

        Texture texture0 = Texture("Textures/dvd.png");
        int slot0 = 0;
        texture0.Bind(slot0);
        shaderProgram.Bind();
        shaderProgram.setInt("u_Texture0", slot0);

        // Unbind all to prevent accidentally modifying them
        vao.Unbind();
        vbo.Unbind();
        ebo.Unbind();
        texture0.Unbind();
        shaderProgram.Unbind();

        Renderer renderer;

        // Specify the color of the background
        GLCall(glClearColor(0.1f, 0.1f, 0.1f, 0.8f));

        float delta = 0.0075, sx = 1, sy = 1; // starting params
        float scale = 0.3; // scale of texture
        float texture_boundary = 0.5f * scale; // texture size size * scale;
        glm::vec3 color(1, 1, 1); // starting color

        srand(static_cast <unsigned> (time(0)));
        auto randomize_color = [&](glm::vec3& col) -> void {
            float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            col[ 0 ] = r;
            r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            col[ 1 ] = r;
            r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            col[ 2 ] = r;
        };

        auto update = [&](float& x, float& y) -> void{
            float y_max = (float)w_Height/w_Width;
            float y_min = -(float)w_Height/w_Width;
            float x_max = 1 ;
            float x_min = -1;

            if( y + texture_boundary >= y_max ) {
                sy = -1;
                randomize_color(color);
            }
            if( y - texture_boundary <= y_min ) {
                sy = 1;
                randomize_color(color);
            }

            if( x + texture_boundary >= x_max ) {
                sx = -1;
                randomize_color(color);
            }
            if( x - texture_boundary <= x_min ) {
                sx = 1;
                randomize_color(color);
            }

            x += sx*delta;
            y += sy*delta;
        };

        float x = 0, y = 0; // starting coords
        while (!glfwWindowShouldClose(window)) {
            renderer.Clear();

            update(x, y);

            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0));
            shaderProgram.Bind();
            glm::mat4 mvp = proj * view * model;
            shaderProgram.setUniformMat4f("u_MVP", mvp);
            shaderProgram.setFloat("scale", scale);
            shaderProgram.setFloat4("t0_Color", color.x, color.y, color.z, 1.0);

            texture0.Bind(slot0);
            renderer.Draw(vao, ebo, shaderProgram);

            // Swap the back buffer with the front buffer
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        // Delete all the objects we've created
        vao.Delete();
        vbo.Delete();
        ebo.Delete();
        shaderProgram.Delete();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
