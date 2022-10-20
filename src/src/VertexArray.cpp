//
// Created by Anshul Saraf on 30/08/22.
//

#include "VertexArray.h"
#include "GLError.h"

// Constructor that generates a VertexArray ID
VertexArray::VertexArray() {
    GLCall(glGenVertexArrays(1, &ID));
}

void VertexArray::AddBuffer(const GLBuffer& xBuffer, const GLBufferLayout& layout) {
    Bind();
    xBuffer.Bind();
    const auto& elements = layout.GetElements();
    uint32_t offset = 0;
    for (uint32_t i = 0; i < elements.size(); i++) {
        const auto& element = elements[ i ];
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(),
                                     (const void*) offset));
        offset += element.count * GLBufferElements::GetSizeOfType(element.type);
    }
//    xBuffer.Unbind();
}

// Binds the VertexArray
void VertexArray::Bind() const {
    GLCall(glBindVertexArray(ID));
}

// Unbinds the VertexArray
void VertexArray::Unbind() const {
    GLCall(glBindVertexArray(0));
}

// Deletes the VertexArray
void VertexArray::Delete() {
    GLCall(glDeleteVertexArrays(1, &ID));
}

VertexArray::~VertexArray() {
//    Delete();
}

