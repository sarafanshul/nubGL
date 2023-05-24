//
// Created by Anshul Saraf on 02/05/23.
//

#ifndef OPENGLBASICS_TEXTURECONVERTERV1_H
#define OPENGLBASICS_TEXTURECONVERTERV1_H
#include <glad/glad.h>
#include "Logger.h"
#include "GLError.h"
#include "TextureConverter.h"

class TextureConverterV1 : public TextureConverter {
public:
    TextureConverterV1(GLsizei width, GLsizei height) : m_width(width), m_height(height), m_fboId(0) {
        // Create the framebuffer object and attach the texture
        GLCall(glGenFramebuffers(1, &m_fboId));
        GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_fboId));
        GLCall(glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 0, 0));
        GLCall(glBindTexture(GL_TEXTURE_2D, 0));
        GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    }

    void convert(GLuint inputTextureId, GLuint externalTextureId) override {
        // Bind the framebuffer object and attach the input texture
        GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_fboId));
        GLCall(glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, inputTextureId, 0));

        // Copy the input texture to the external texture using glCopyTexSubImage2D
        GLCall(glBindTexture(GL_TEXTURE_2D, externalTextureId));
        GLCall(glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, m_width, m_height));
        GLCall(glBindTexture(GL_TEXTURE_2D, 0));

        // Detach the input texture from the framebuffer object
        GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 0, 0));
        GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    }

    ~TextureConverterV1() override {
        GLCall(glDeleteFramebuffers(1, &m_fboId));
    }

private:
    GLsizei m_width;
    GLsizei m_height;
    GLuint m_fboId;
};

#endif //OPENGLBASICS_TEXTURECONVERTERV1_H
