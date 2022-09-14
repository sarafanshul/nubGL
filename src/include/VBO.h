//
// Created by Anshul Saraf on 30/08/22.
//

#ifndef OPENGLBASICS_VBO_H
#define OPENGLBASICS_VBO_H

#include<glad/glad.h>
#include "GLBuffer.h"

class VBO : public GLBuffer{
public:
    // Reference ID of the Vertex GLBuffer Object
    GLuint ID;

    // Constructor that generates a Vertex GLBuffer Object, binds it, and links it to vertices
    VBO(GLfloat* vertices, GLsizeiptr size);

    // Binds the VBO
    void Bind() const override;

    // Unbinds the VBO
    void Unbind() const override;

    // Deletes the VBO
    void Delete() override;

    ~VBO();
};


#endif //OPENGLBASICS_VBO_H
