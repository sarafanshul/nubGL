//
// Created by Anshul Saraf on 15/09/22.
//

#ifndef OPENGLBASICS_RENDERER_H
#define OPENGLBASICS_RENDERER_H

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer{
public:

    void Clear() const;
    void Draw( const VertexArray& vao, const IndexBuffer& ebo, const Shader& shader ) const;
};

#endif //OPENGLBASICS_RENDERER_H
