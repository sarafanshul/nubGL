//
// Created by Anshul Saraf on 08/09/22.
//

#ifndef OPENGLBASICS_GLERROR_H
#define OPENGLBASICS_GLERROR_H

#include <glad/glad.h>
#include <iostream>
#include <csignal>

#define ASSERT(x) if (!(x)) std::raise(SIGKILL)

static std::string glGetErrorString(GLenum error){
    switch (error){
        case GL_NO_ERROR:          return "No Error";
        case GL_INVALID_ENUM:      return "Invalid Enum";
        case GL_INVALID_VALUE:     return "Invalid Value";
        case GL_INVALID_OPERATION: return "Invalid Operation";
        case GL_INVALID_FRAMEBUFFER_OPERATION: return "Invalid Framebuffer Operation";
        case GL_OUT_OF_MEMORY:     return "Out of Memory";
        default:                   return "Unknown Error : " + std::to_string(error);
    }
}

static void GLClearError(){
    while (glGetError() != GL_NO_ERROR);
}

static bool GLCheckError(){
    GLenum error = glGetError();
    while (error != GL_NO_ERROR){
        std::cerr << "[OpenGL Error]" << "-->" << glGetErrorString(error) << std::endl;
        error = glGetError();
        return false;
    }
    return true;
}

static bool __GLLogCall(const char* function, const char* file, int line){
    GLenum error = glGetError();
    while (error != GL_NO_ERROR){
        std::cerr << "[OpenGL Error]" << function  << ":" << file << ":" << line << "-->" << glGetErrorString(error) << std::endl;
        error = glGetError();
        return false;
    }
    return true;
}

#define GLCall(x) GLClearError();\
    x;\
    ASSERT(__GLLogCall(#x, __FILE__, __LINE__))


#endif //OPENGLBASICS_GLERROR_H
