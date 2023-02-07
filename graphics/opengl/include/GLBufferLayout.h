//
// Created by Anshul Saraf on 15/09/22.
//

#ifndef OPENGLBASICS_GLBUFFERLAYOUT_H
#define OPENGLBASICS_GLBUFFERLAYOUT_H

#include "glad/glad.h"
#include "vector"
#include "GLError.h"

struct GLBufferElements {
    uint32_t type;
    uint32_t count;
    unsigned char normalized;

    static uint32_t GetSizeOfType(uint32_t type) {
        switch (type) {
            case GL_FLOAT         :
                return sizeof(GLfloat);
            case GL_UNSIGNED_INT  :
                return sizeof(GLuint);
            case GL_UNSIGNED_BYTE :
                return sizeof(GLbyte);
        }
        ASSERT(false);
        return 0;
    }
};

class GLBufferLayout {
public:
    GLBufferLayout() : m_Stride(0) {};

    template<typename T>
    void Push(uint32_t count) {
        ASSERT(false);
    }

    template<>
    void Push<float>(uint32_t count) {
        m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
        m_Stride += count * GLBufferElements::GetSizeOfType(GL_FLOAT);
    }

    template<>
    void Push<unsigned int>(uint32_t count) {
        m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
        m_Stride += count * GLBufferElements::GetSizeOfType(GL_UNSIGNED_INT);
    }

    template<>
    void Push<unsigned char>(uint32_t count) {
        m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
        m_Stride += count * GLBufferElements::GetSizeOfType(GL_UNSIGNED_BYTE);
    }

    [[nodiscard]] inline uint32_t GetStride() const { return m_Stride; }

    [[nodiscard]] inline std::vector<GLBufferElements> GetElements() const { return m_Elements; }

private:
    std::vector<GLBufferElements> m_Elements;
    uint32_t m_Stride = 0;
};

#endif //OPENGLBASICS_GLBUFFERLAYOUT_H
