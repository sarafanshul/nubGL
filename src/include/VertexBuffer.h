//
// Created by Anshul Saraf on 30/08/22.
//

#ifndef OPENGLBASICS_VERTEXBUFFER_H
#define OPENGLBASICS_VERTEXBUFFER_H

#include<glad/glad.h>
#include "GLBuffer.h"

class VertexBuffer : public GLBuffer {
public:
    // Constructor that generates a Vertex GLBuffer Object, binds it, and links it to vertices
    VertexBuffer(GLfloat* vertices, GLsizeiptr size);

    // Binds the VertexBuffer
    void Bind() const override;

    // Unbinds the VertexBuffer
    void Unbind() const override;

    // Deletes the VertexBuffer
    void Delete() override;

    ~VertexBuffer();

private:
    // Reference ID of the Vertex GLBuffer Object
    GLuint ID;
};


#endif //OPENGLBASICS_VERTEXBUFFER_H
