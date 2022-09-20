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
#include "glm/glm.hpp"

std::string get_file_contents(const char* filename);

class Shader {
public:

    Shader(const char* vertexFile, const char* fragmentFile);

    void Bind() const;

    void Unbind() const;

    void Delete();

    [[maybe_unused]] void setBool(const std::string& name, bool value);

    [[maybe_unused]] void setInt(const std::string& name, int value);

    [[maybe_unused]] void setFloat(const std::string& name, float value);

    [[maybe_unused]] void setFloat4(const std::string& name, float v1, float v2, float v3, float v4);

    [[maybe_unused]] void setUniformMat4f(const std::string& name, const glm::mat4& matrix);

    ~Shader();

private:
    static GLuint compileShaders(const char* source, GLint type);

    [[nodiscard]] GLuint GetUniformLocation(const std::string& name);

    // Checks if the different Shaders have compiled properly
    static void compileErrors(unsigned int shader, GLint type);

    std::unordered_map<std::string, GLint> uniformLocationCache;
    GLuint ID;
};

#endif //OPENGLBASICS_SHADER_H
