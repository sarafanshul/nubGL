//
// Created by Anshul Saraf on 30/08/22.
//

#include "IndexBuffer.h"
#include "GLError.h"

// Constructor that generates an Elements GLBuffer Object, binds it, and links it to indices
IndexBuffer::IndexBuffer(GLuint* indices, GLsizeiptr size) :
IndexBuffer(indices, size, GL_STATIC_DRAW){}


IndexBuffer::IndexBuffer(GLuint* indices, GLsizeiptr size, GLenum usage) {
    m_Count = indices ? (size / sizeof(indices[ 0 ])) : 0;
    GLCall(glGenBuffers(1, &ID));
    Bind();
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, usage));
}

// Binds the IndexBuffer
void IndexBuffer::Bind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID));
}

void IndexBuffer::SetBufferSubData(GLuint* indices, GLsizeiptr size, GLintptr offset) {
    Bind();
    m_Count = indices ? (size / sizeof(indices[ 0 ])) : 0;
    GLCall( glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, indices) );
}

// Unbinds the IndexBuffer
void IndexBuffer::Unbind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

// Deletes the IndexBuffer
void IndexBuffer::Delete() {
    GLCall(glDeleteBuffers(1, &ID));
}

IndexBuffer::~IndexBuffer() {
//    Delete();
}

uint32_t IndexBuffer::GetCount() const {
    return m_Count;
}
