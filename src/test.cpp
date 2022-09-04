//
// Created by Anshul Saraf on 05/09/22.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

template<typename T>
using scope = std::unique_ptr<T>;

template<typename T, typename ... Args>
constexpr scope<T> create(Args& ... args){
    return std::make_unique<T>(std::forward<Args>(args) ...);
}

static GLuint CompileShader(const GLuint type, const std::string& source){
    GLuint shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    int result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

    if(result == GL_FALSE){
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        auto message = (char *)alloca(length * sizeof(char));
        glGetShaderInfoLog(shader, length, &length, message);

        std::cerr << "Failed to compile Shader : " << type << std::endl;
        std::cerr << message << std::endl;
        glDeleteShader(shader);

        return -1;
    }

    return shader;
};

static GLuint CreateShader( const std::string& vertexShader, const std::string& fragmentShader ){

    GLuint program = glCreateProgram();
    auto vShader = CompileShader(GL_VERTEX_SHADER, vertexShader);
    auto fShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vShader);
    glAttachShader(program, fShader);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vShader);
    glDeleteShader(fShader);

    return program;
}

int main(){
    GLFWwindow* window;

    if( !glfwInit() )
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


    if ( ! (window = glfwCreateWindow(800, 800, "test", 0, 0)) ){
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGL()){
        std::cerr << "Failed to initialize library loader " << std::endl;
    }

    float positions[6] = {
            -0.5f, -0.5f,
             0.0f,  0.5f,
             0.5f, -0.5f,
    };

    GLuint buffer, vao;
    glGenBuffers(1, &buffer);
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float ), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float ) * 2, 0);

    std::string vertexShader = R"(
#version 330 core
layout (location = 0) in vec4 position;
void main(){
    gl_Position = position;
}

    )";

    std::string fragmentShader = R"(
#version 330 core
layout (location = 0) out vec4 color; // rgba
void main(){
    color = vec4(1.0, 0.0, 0.0, 1.0);
}

    )";

    GLuint shader = CreateShader(vertexShader, fragmentShader);
    glUseProgram(shader);

    while ( !glfwWindowShouldClose(window) ){

        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);

        glfwPollEvents();

    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &buffer);
    glDeleteProgram(shader);
    return 0;
};
