//
// Created by Anshul Saraf on 30/08/22.
//

#ifndef OPENGLBASICS_EBO_H
#define OPENGLBASICS_EBO_H

#include<glad/glad.h>

class EBO{
public:
    // ID reference of Elements Buffer Object
    GLuint ID;

    // Constructor that generates an Elements Buffer Object, binds it, and links it to indices
    EBO(GLuint* indices, GLsizeiptr size);

    // Binds the EBO
    void Bind();

    // Unbinds the EBO
    void Unbind();

    // Deletes the EBO

    void Delete();
};

#endif //OPENGLBASICS_EBO_H
