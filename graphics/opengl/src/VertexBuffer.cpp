//
// Created by Anshul Saraf on 30/08/22.
//

#include "VertexBuffer.h"
#include "GLError.h"

// Constructor that generates a Vertex GLBuffer Object, binds it, and links it to vertices
VertexBuffer::VertexBuffer(GLfloat* vertices, GLsizeiptr size) :
    VertexBuffer(vertices, size, GL_STATIC_DRAW){}

VertexBuffer::VertexBuffer(GLfloat* vertices, GLsizeiptr size, GLenum usage) {
    m_Usage = usage;
    GLCall(glGenBuffers(1, &ID));
    Bind();
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, vertices, m_Usage));
}

// Binds the VertexBuffer
void VertexBuffer::Bind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, ID));
}

// Sets buffer SubData
void VertexBuffer::SetBufferSubData(GLfloat* vertices, GLsizeiptr size, GLintptr offset) {
    Bind();
    GLCall( glBufferSubData(GL_ARRAY_BUFFER, offset, size, vertices) );
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
