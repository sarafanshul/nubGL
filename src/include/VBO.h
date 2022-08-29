//
// Created by Anshul Saraf on 30/08/22.
//

#ifndef OPENGLBASICS_VBO_H
#define OPENGLBASICS_VBO_H

#include<glad/glad.h>

class VBO{
public:
    // Reference ID of the Vertex Buffer Object
    GLuint ID;

    // Constructor that generates a Vertex Buffer Object, binds it, and links it to vertices
    VBO(GLfloat* vertices, GLsizeiptr size);

    // Binds the VBO
    void Bind();
    // Unbinds the VBO

    void Unbind();
    // Deletes the VBO

    void Delete();
};


#endif //OPENGLBASICS_VBO_H
