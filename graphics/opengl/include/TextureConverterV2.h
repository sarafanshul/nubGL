//
// Created by Anshul Saraf on 03/05/23.
//

#ifndef OPENGLBASICS_TEXTURECONVERTERV2_H
#define OPENGLBASICS_TEXTURECONVERTERV2_H
#include <glad/glad.h>
#include "Logger.h"
#include "GLError.h"
#include "Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "TextureConverter.h"

/**
 * Shader based textureConverter for primitive types.
 * we set draw_frame-buffer to output texture.
 */
class TextureConverterV2 : public TextureConverter{
public:
    TextureConverterV2( GLuint width, GLuint height ) : m_width(width), m_height(height), m_fboId(0) {
        const char* vertexShaderSrc = R"(
            #version 330 core
            layout (location = 0)in vec2 a_position;
            layout (location = 1)in vec2 a_texCoord;
            out vec2 v_texCoord;
            void main() {
                gl_Position = vec4(a_position, 0.0, 1.0);
                v_texCoord = a_texCoord;
            }
        )";
        const char* fragmentShaderSrc = R"(
            #version 330 core
            precision mediump float;
            layout(location = 0) out vec4 color;
            in vec2 v_texCoord;
            uniform sampler2D u_inputTexture;

            void main() {
                color = texture(u_inputTexture, v_texCoord);
            }
        )";

        // set up vertex data for rendering a full-screen quad
        static GLfloat vertexData[] = {
                -1.0f, -1.0f, 0.0f, 0.0f,
                 1.0f, -1.0f, 1.0f, 0.0f,
                -1.0f,  1.0f, 0.0f, 1.0f,
                 1.0f,  1.0f, 1.0f, 1.0f,
        };
        static GLuint indices[] = {
                0, 1, 2,
                1, 2, 3,
        };

        shaderProgram = CreateScope<Shader>(vertexShaderSrc, fragmentShaderSrc, true);

        vertexArray = CreateScope<VertexArray>();
        vertexArray->Bind();

        vertexBuffer = CreateScope<VertexBuffer>(vertexData, sizeof(vertexData));
        indexBuffer = CreateScope<IndexBuffer>(indices, sizeof(indices)) ;

        GLBufferLayout layout;
        layout.Push<float>(2); //aPos
        layout.Push<float>(2); // u_Texture coords

        vertexArray->AddBuffer(*vertexBuffer, layout);

        vertexArray->Unbind();
        vertexBuffer->Unbind();
        indexBuffer->Unbind();
        shaderProgram->Unbind();

        GLCall(glGenFramebuffers(1, &m_fboId));
        GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_fboId));
        GLCall(glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 0, 0));
        GLCall(glBindTexture(GL_TEXTURE_2D, 0));
        GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));

    }

    void convert(GLuint inputTextureId, GLuint externalTextureId) override{

        // save original viewport
        GLint aiViewport[4];
        glGetIntegerv(GL_VIEWPORT, aiViewport);

        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        GLCall(glViewport(0, 0, m_width, m_height));

        GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_fboId));
        GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, externalTextureId, 0));
        GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
        GLCall(glDrawBuffers(1, DrawBuffers)); // "1" is the size of DrawBuffers

        shaderProgram->Bind();
        vertexArray->Bind();
        indexBuffer->Bind();
        shaderProgram->setInt("u_inputTexture", 0);
        GLCall( glActiveTexture(GL_TEXTURE0) );
        GLCall( glBindTexture(GL_TEXTURE_2D, inputTextureId) );

        GLCall( glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr) );

        GLCall( glBindFramebuffer(GL_FRAMEBUFFER, 0));
        GLCall( glBindTexture(GL_TEXTURE_2D, 0) );
        vertexArray->Unbind();
        vertexBuffer->Unbind();
        indexBuffer->Unbind();
        shaderProgram->Unbind();

        // restore original viewport
        glViewport(aiViewport[0], aiViewport[1], (GLsizei)aiViewport[2], (GLsizei)aiViewport[3]);
    }

    ~TextureConverterV2() override{
        GLCall(glDeleteFramebuffers(1, &m_fboId));

        vertexArray->Delete();
        vertexArray.reset();

        vertexBuffer->Delete();
        vertexBuffer.reset();

        indexBuffer->Delete();
        indexBuffer.reset();

        shaderProgram->Delete();
        shaderProgram.reset();
    }

private:
    GLsizei m_width;
    GLsizei m_height;
    GLuint m_fboId;

    Scope<Shader> shaderProgram;
    Scope<VertexArray> vertexArray;
    Scope<VertexBuffer> vertexBuffer;
    Scope<IndexBuffer> indexBuffer;
};
#endif //OPENGLBASICS_TEXTURECONVERTERV2_H
