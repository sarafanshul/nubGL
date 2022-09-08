//
// Created by Anshul Saraf on 30/08/22.
//

#ifndef OPENGLBASICS_SHADER_H
#define OPENGLBASICS_SHADER_H

#include "glad/glad.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class Shader{
public:
    GLuint ID;
    Shader(const char* vertexFile, const char* fragmentFile);

    void Activate() const;
    void Delete();

    void setBool(const std::string &name, bool value);
    void setInt(const std::string &name, int value);
    void setFloat(const std::string &name, float value);

    ~Shader();

private:
    // Checks if the different Shaders have compiled properly
    static void compileErrors(unsigned int shader, GLint type);

    static GLuint compileShaders(const char* source, GLint type);
};

#endif //OPENGLBASICS_SHADER_H
