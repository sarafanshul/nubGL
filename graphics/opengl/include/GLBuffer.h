//
// Created by Anshul Saraf on 15/09/22.
//

#ifndef OPENGLBASICS_GLBUFFER_H
#define OPENGLBASICS_GLBUFFER_H

class GLBuffer {
public:
    // Binds THe GLBuffer
    virtual void Bind() const = 0;

    // Unbinds the GLBuffer
    virtual void Unbind() const = 0;

    // Deletes the GLBuffer
    virtual void Delete() = 0;
};

#endif //OPENGLBASICS_GLBUFFER_H
