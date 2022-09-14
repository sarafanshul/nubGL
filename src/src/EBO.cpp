//
// Created by Anshul Saraf on 30/08/22.
//

#include "EBO.h"
#include "GLError.h"

// Constructor that generates an Elements GLBuffer Object, binds it, and links it to indices
EBO::EBO(GLuint* indices, GLsizeiptr size){
    GLCall(glGenBuffers(1, &ID));
    Bind();
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW));
}

// Binds the EBO
void EBO::Bind() const{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID));
}

// Unbinds the EBO
void EBO::Unbind() const{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

// Deletes the EBO
void EBO::Delete(){
    GLCall(glDeleteBuffers(1, &ID));
}

EBO::~EBO() {
//    Delete();
}
