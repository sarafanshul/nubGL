//
// Created by Anshul Saraf on 30/08/22.
//

#ifndef OPENGLBASICS_VERTEXARRAY_H
#define OPENGLBASICS_VERTEXARRAY_H

#include"glad/glad.h"
#include"VertexBuffer.h"
#include "GLBuffer.h"
#include "GLBufferLayout.h"

class VertexArray {
public:
    // Constructor that generates a VertexArray ID
    VertexArray();

    // binds a buffer layout.
    void AddBuffer(const GLBuffer& xBuffer, const GLBufferLayout& layout);

    // Binds the VertexArray
    void Bind() const;

    // Unbinds the VertexArray
    void Unbind() const;

    // Deletes the VertexArray
    void Delete();

    ~VertexArray();

private:
    // ID reference for the Vertex Array Object
    GLuint ID;
};

#endif //OPENGLBASICS_VERTEXARRAY_H
