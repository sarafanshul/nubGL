//
// Created by Anshul Saraf on 30/08/22.
//

#ifndef OPENGLBASICS_INDEXBUFFER_H
#define OPENGLBASICS_INDEXBUFFER_H

#include"glad/glad.h"
#include "GLBuffer.h"

class IndexBuffer : public GLBuffer {
public:
    // Constructor that generates an Elements GLBuffer Object, binds it, and links it to indices
    IndexBuffer(GLuint* indices, GLsizeiptr size);

    IndexBuffer(GLuint* indices, GLsizeiptr size, GLenum usage);

    // Binds the IndexBuffer
    void Bind() const override;

    void SetBufferSubData(GLuint* indices, GLsizeiptr size, GLintptr offset = 0);

    // Unbinds the IndexBuffer
    void Unbind() const override;

    // Deletes the IndexBuffer
    void Delete() override;

    [[nodiscard]] uint32_t GetCount() const;

    ~IndexBuffer();

private:
    // ID reference of Elements GLBuffer Object
    GLuint ID;
    uint32_t m_Count;
};

#endif //OPENGLBASICS_INDEXBUFFER_H
