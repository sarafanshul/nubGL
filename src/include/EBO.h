//
// Created by Anshul Saraf on 30/08/22.
//

#ifndef OPENGLBASICS_EBO_H
#define OPENGLBASICS_EBO_H

#include<glad/glad.h>
#include "GLBuffer.h"

class EBO : public GLBuffer{
public:
    // ID reference of Elements GLBuffer Object
    GLuint ID;

    // Constructor that generates an Elements GLBuffer Object, binds it, and links it to indices
    EBO(GLuint* indices, GLsizeiptr size);

    // Binds the EBO
    void Bind() const override;

    // Unbinds the EBO
    void Unbind() const override;

    // Deletes the EBO
    void Delete() override;

    ~EBO();
};

#endif //OPENGLBASICS_EBO_H
