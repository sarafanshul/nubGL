//
// Created by Anshul Saraf on 04/05/23.
//

#ifndef OPENGLBASICS_TEXTURECONVERTER_H
#define OPENGLBASICS_TEXTURECONVERTER_H

class TextureConverter{
public:
    virtual void convert(GLuint inputTextureId, GLuint externalTextureId) = 0;
    virtual ~TextureConverter() = default;
};

#endif //OPENGLBASICS_TEXTURECONVERTER_H
