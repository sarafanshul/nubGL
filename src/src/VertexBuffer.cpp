//
// Created by Anshul Saraf on 30/08/22.
//

#include "VertexBuffer.h"
#include "GLError.h"

// Constructor that generates a Vertex GLBuffer Object, binds it, and links it to vertices
VertexBuffer::VertexBuffer(GLfloat* vertices, GLsizeiptr size) {
    GLCall(glGenBuffers(1, &ID));
    Bind();
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));
}

// Binds the VertexBuffer
void VertexBuffer::Bind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, ID));
}

// Unbinds the VertexBuffer
void VertexBuffer::Unbind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

// Deletes the VertexBuffer
void VertexBuffer::Delete() {
    GLCall(glDeleteBuffers(1, &ID));
}

VertexBuffer::~VertexBuffer() {
//    Delete();
}
