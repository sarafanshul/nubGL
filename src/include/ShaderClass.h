//
// Created by Anshul Saraf on 30/08/22.
//

#ifndef OPENGLBASICS_SHADERCLASS_H
#define OPENGLBASICS_SHADERCLASS_H

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

    void Activate();
    void Delete();
};

#endif //OPENGLBASICS_SHADERCLASS_H
