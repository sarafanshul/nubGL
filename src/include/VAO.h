//
// Created by Anshul Saraf on 30/08/22.
//

#ifndef OPENGLBASICS_VAO_H
#define OPENGLBASICS_VAO_H

#include<glad/glad.h>
#include"VBO.h"
#include "GLBuffer.h"
#include "GLBufferLayout.h"

class VAO{
public:
    // ID reference for the Vertex Array Object
    GLuint ID;
    // Constructor that generates a VAO ID
    VAO();

    // binds a buffer layout.
    void AddBuffer(const GLBuffer& xBuffer, const GLBufferLayout& layout);

    // Binds the VAO
    void Bind() const;

    // Unbinds the VAO
    void Unbind() const;

    // Deletes the VAO
    void Delete();

    ~VAO();
};

#endif //OPENGLBASICS_VAO_H
