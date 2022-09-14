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
#include <unordered_map>

std::string get_file_contents(const char* filename);

class Shader{
public:
    GLuint ID;
    Shader(const char* vertexFile, const char* fragmentFile);

    void Bind() const;
    void Unbind() const;
    void Delete();

    void setBool(const std::string& name, bool value);
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);
    void setFloat4(const std::string& name, float v1, float v2, float v3, float v4);

    ~Shader();

private:
    static GLuint compileShaders(const char* source, GLint type);

    [[nodiscard]] GLuint GetUniformLocation(const std::string& name);

    // Checks if the different Shaders have compiled properly
    static void compileErrors(unsigned int shader, GLint type);

    std::unordered_map<std::string , GLuint > uniformLocationCache;
};

#endif //OPENGLBASICS_SHADER_H
