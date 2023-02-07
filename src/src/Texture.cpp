//
// Created by Anshul Saraf on 17/09/22.
//

#include "Texture.h"
#include "GLError.h"
#include "stb_image.h"

Texture::Texture(int width, int height, int bpp) :
    ID(0), m_Width(width), m_Height(height), m_BPP(bpp)
    {

    GLCall( glGenTextures(1, &ID) );
    GLCall( glBindTexture(GL_TEXTURE_2D, ID) );

    GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR   ) );
    GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR                 ) );

    GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S    , GL_CLAMP_TO_BORDER) );
    GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T    , GL_CLAMP_TO_BORDER) );

    int size = m_Width * m_Height * m_BPP ;
    auto* pData = new unsigned char[size];
    memset(pData, 0xFF, size * sizeof(unsigned char)); // empty white
//    GLCall( glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_BYTE, pData));
    GLCall( glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pData ) );
    GLCall( glGenerateMipmap(GL_TEXTURE_2D) );
    delete[] pData;
    // unbind the texture.
    GLCall( glBindTexture(GL_TEXTURE_2D, 0) );
}


Texture::Texture(const std::string& path, uint32_t flip) :
    ID(0), m_FilePath(path),
    m_Width(0), m_Height(0), m_BPP(0)
    {

    stbi_set_flip_vertically_on_load(flip);
    unsigned char* m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

    if(!m_LocalBuffer){
        std::cerr << "Error: Failed to load texture" << std::endl;
        std::cerr << stbi_failure_reason() << std::endl;
        ASSERT(false);
    }

    // Generate Textures
    GLCall( glGenTextures(1, &ID) );
    // bind
    GLCall( glBindTexture(GL_TEXTURE_2D, ID) );

    // Texture Filtering
    /* GL_NEAREST results in blocked patterns where we can clearly see the pixels that form the texture while
     * GL_LINEAR produces a smoother pattern where the individual pixels are less visible.
     *
     * Texture filtering can be set for magnifying and minifying operations (when scaling up or downwards)
     * so you could for example use nearest neighbor filtering when textures are scaled downwards
     * and linear filtering for upscaled textures.
     * We thus have to specify the filtering method for both options via glTexParameter*.
     *
     * A common mistake is to set one of the mipmap filtering options as the **magnification filter**.
     * This doesn't have any effect since mipmaps are primarily used for when textures get downscaled:
     *  texture magnification doesn't use mipmaps and giving it a mipmap filtering option will generate
     *  an OpenGL GL_INVALID_ENUM error code.
     * */
    GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR   ) );
    GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR                 ) );

    // Texture wrapping
    /* GL_REPEAT: The default behavior for textures. Repeats the texture image.
     * GL_MIRRORED_REPEAT: Same as GL_REPEAT but mirrors the image with each repeat.
     * GL_CLAMP_TO_EDGE: Clamps the coordinates between 0 and 1. The result is that higher coordinates become clamped to the edge, resulting in a stretched edge pattern.
     * GL_CLAMP_TO_BORDER: Coordinates outside the range are now given a user-specified border color.
     */
    GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S    , GL_CLAMP_TO_BORDER) );
    GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T    , GL_CLAMP_TO_BORDER) );

    // Set Border Color
    float borderColor[] = { 0.5f, 0.5f, 0.5f, 0.5f };
    GLCall( glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor) );

    // specify a two-dimensional texture image https://docs.gl/gl4/glTexImage2D
    GLCall( glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer ) );

    GLCall( glGenerateMipmap(GL_TEXTURE_2D) );

    // unbind the texture.
    GLCall( glBindTexture(GL_TEXTURE_2D, 0) );

    if(m_LocalBuffer) { // free image data
        stbi_image_free(m_LocalBuffer);
    }
}

void Texture::Bind(uint32_t slot) const {
    // The main purpose of texture units is to allow us to use more than 1 texture in our shaders.
    // By assigning texture units to the samplers, we can bind to multiple textures at once
    // as long as we activate the corresponding texture unit first
    GLCall( glActiveTexture(GL_TEXTURE0 + slot) );
    GLCall( glBindTexture(GL_TEXTURE_2D, ID) );
}

void Texture::Unbind() {
    GLCall( glBindTexture(GL_TEXTURE_2D, 0) );
}

Texture::~Texture() {
    GLCall( glDeleteTextures(1, &ID) );
}
