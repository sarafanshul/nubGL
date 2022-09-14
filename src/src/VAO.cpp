//
// Created by Anshul Saraf on 30/08/22.
//

#include"VAO.h"
#include "GLError.h"

// Constructor that generates a VAO ID
VAO::VAO(){
    GLCall(glGenVertexArrays(1, &ID));
}

void VAO::AddBuffer(const GLBuffer &xBuffer, const GLBufferLayout &layout) {
    Bind();
    xBuffer.Bind();
    const auto& elements = layout.GetElements();
    uint32_t offset = 0 ;
    for(uint32_t i = 0 ; i < elements.size() ; i++) {
        const auto& element = elements[i];
        GLCall(glEnableVertexAttribArray( i ));
        GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
        offset += element.count * GLBufferElements::GetSizeOfType(element.type) ;
    }
//    xBuffer.Unbind();
}

// Binds the VAO
void VAO::Bind() const{
    GLCall(glBindVertexArray(ID));
}

// Unbinds the VAO
void VAO::Unbind() const{
    GLCall(glBindVertexArray(0));
}

// Deletes the VAO
void VAO::Delete(){
    GLCall(glDeleteVertexArrays(1, &ID));
}

VAO::~VAO() {
//    Delete();
}

