//
// Created by Anshul Saraf on 30/08/22.
//

#include"VAO.h"
#include "GLError.h"

// Constructor that generates a VAO ID
VAO::VAO(){
    GLCall(glGenVertexArrays(1, &ID));
}

// Links a VBO to the VAO using a certain layout
void VAO::LinkVBO(VBO& VBO, GLuint layout, GLint numComponents, GLenum type, GLsizei stride, void* offset){
    VBO.Bind();
    GLCall(glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset));
    GLCall(glEnableVertexAttribArray(layout));
    VBO.Unbind();
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
