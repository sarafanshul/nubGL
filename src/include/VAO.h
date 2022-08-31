//
// Created by Anshul Saraf on 30/08/22.
//

#ifndef OPENGLBASICS_VAO_H
#define OPENGLBASICS_VAO_H

#include<glad/glad.h>
#include"VBO.h"

class VAO{
public:
    // ID reference for the Vertex Array Object
    GLuint ID;
    // Constructor that generates a VAO ID
    VAO();

    // Links a VBO to the VAO using a certain layout
    void LinkVBO(VBO& VBO, GLuint layout, GLint numComponents, GLenum type, GLsizei stride, void* offset);

    // Binds the VAO
    void Bind();

    // Unbinds the VAO
    void Unbind();

    // Deletes the VAO
    void Delete();
};

#endif //OPENGLBASICS_VAO_H
