//
// Created by Anshul Saraf on 04/03/23.
//

#include "Renderer2D.h"
#include "IndexBuffer.h"

void Renderer2D::Init() {
    s_Data = new Renderer2DStorage() ;
    s_Data->QuadVertexArray = CreateRef<VertexArray>();

    float squareVertices[5 * 4] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
    };

    Ref<VertexBuffer> squareVB = CreateRef<VertexBuffer>(squareVertices, sizeof(squareVertices));

    GLBufferLayout layout;
    layout.Push<float>(3); // "a_Position"
    layout.Push<float>(2); // "a_TexCoord"

    s_Data->QuadVertexArray->AddBuffer(*squareVB, layout);

    uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
    Ref<IndexBuffer> squareIB = CreateRef<IndexBuffer>(squareIndices, sizeof(squareIndices));
//    s_Data->QuadVertexArray->SetIndexBuffer(squareIB);

    s_Data->WhiteTexture = CreateRef<Texture2D>(1, 1, 8);
    uint32_t whiteTextureData = 0xffffffff;
//    s_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

//    s_Data->TextureShader = Shader::Create("assets/shaders/Texture.glsl");
    s_Data->TextureShader->Bind();
//    s_Data->TextureShader->SetInt("u_Texture", 0);

}

void Renderer2D::Shutdown() {

}

void Renderer2D::BeginScene(const OrthographicCamera& camera) {

}

void Renderer2D::EndScene() {

}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {

}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {

}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color) {

}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color) {

}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture) {

}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture) {

}

void
Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture,
                     const glm::vec4& color) {

}

void
Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture,
                     const glm::vec4& color) {

}
