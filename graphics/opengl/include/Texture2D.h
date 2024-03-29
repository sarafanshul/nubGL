//
// Created by Anshul Saraf on 17/09/22.
//

#ifndef OPENGLBASICS_TEXTURE2D_H
#define OPENGLBASICS_TEXTURE2D_H

#include "glad/glad.h"
#include <string>

/**
 * Abstraction for GL Texture2D
 * https://learnopengl.com/Getting-started/Textures
 */
class Texture2D {
public:

    explicit Texture2D(const std::string& path, uint32_t flip = 1);

    explicit Texture2D(int width, int height, int bpp);

    void Bind(uint32_t slot = 0) const;

    void Unbind();

    [[nodiscard]] int GetWidth() const {return m_Width; };
    [[nodiscard]] int GetHeight() const {return m_Height; };
    [[nodiscard]] int GetBPP() const {return m_BPP; };

    operator GLuint() const { return ID;};

    ~Texture2D();

private:
    GLuint ID;
    std::string m_FilePath;
    int m_Width, m_Height, m_BPP;
};


#endif //OPENGLBASICS_TEXTURE2D_H
