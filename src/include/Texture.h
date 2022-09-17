//
// Created by Anshul Saraf on 17/09/22.
//

#ifndef OPENGLBASICS_TEXTURE_H
#define OPENGLBASICS_TEXTURE_H

#include "glad/glad.h"
#include <string>

/**
 * Abstraction for GL Texture2D
 * https://learnopengl.com/Getting-started/Textures
 */
class Texture {
public:

    explicit Texture(const std::string& path, uint32_t flip = 1);

    void Bind(uint32_t slot = 0) const;

    void Unbind();

    ~Texture();

private:
    GLuint ID;
    std::string m_FilePath;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;
};


#endif //OPENGLBASICS_TEXTURE_H
