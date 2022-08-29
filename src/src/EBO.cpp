//
// Created by Anshul Saraf on 30/08/22.
//

#include "EBO.h"

// Constructor that generates an Elements Buffer Object, binds it, and links it to indices
EBO::EBO(GLuint* indices, GLsizeiptr size){
    glGenBuffers(1, &ID);
    Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

// Binds the EBO
void EBO::Bind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

// Unbinds the EBO
void EBO::Unbind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Deletes the EBO
void EBO::Delete(){
    glDeleteBuffers(1, &ID);
}
