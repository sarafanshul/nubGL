//
// Created by Anshul Saraf on 03/01/23.
//


#include "../TestTexture2D.h"
#include "imgui.h"


Test::TestTexture2D::TestTexture2D() {

    GLfloat vertices[] = {
//            x      y     z        t_x   t_y
            -0.5,  -0.5,  0.0,     0.0f,  0.0f,    // bottom left
             0.5,  -0.1,  0.0,     1.0f,  0.0f,    // bottom right
             0.5,   0.5,  0.0,     1.0f,  1.0f,    // top right
            -0.5,   0.5,  0.0,     0.0f,  1.0f,    // top left
    };

    uint indices[] = {
            0, 1, 3, // triangle 1
            1, 3, 2, // triangle 2
    };

    shaderProgram = CreateScope<Shader>(vert_shader_path.c_str(), frag_shader_path.c_str()) ;

    // set blinding params
    GLCall( glEnable(GL_BLEND) );
    GLCall( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );

    vertexArray = CreateScope<VertexArray>();
    vertexArray->Bind();

    vertexBuffer = CreateScope<VertexBuffer>(vertices, sizeof(vertices));
    indexBuffer = CreateScope<IndexBuffer>(indices, sizeof(indices)) ;

    GLBufferLayout layout;
    layout.Push<float>(3); //aPos
    layout.Push<float>(2); // u_Texture coords

    vertexArray->AddBuffer(*vertexBuffer, layout);

    texture0 = CreateScope<Texture2D>(texture_path);

#if TEXTURE_CONVERTER
    converter = CreateScope<TextureConverterV2>(texture0->GetWidth(), texture0->GetHeight());
    renderTexture = CreateScope<Texture2D>(texture0->GetWidth(), texture0->GetHeight(), 4);
#endif
//    shaderProgram->Bind();
//    texture0->Bind(slot0);
//    shaderProgram->setInt("u_Texture0", slot0);

    vertexArray->Unbind();
    vertexBuffer->Unbind();
    indexBuffer->Unbind();
    texture0->Unbind();
    shaderProgram->Unbind();

#if COPY_TEXTURE
    texture1 = CreateScope<Texture2D>(
            texture0->GetWidth(),
            texture0->GetHeight(),
            texture0->GetBPP() ) ;

    GLCall(glGenFramebuffers(1, &fbo));
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *texture1, 0);
    // check for framebuffer completeness
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "framebuffer config failed, status : " << status << std::endl;
        ASSERT(0);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    {
        // Create a simple vertex and fragment shader
        const char* vertexShaderSource = "#version 330 core\nlayout(location = 0) in vec2 aPos;\nout vec2 TexCoord;\nvoid main()\n{\ngl_Position = vec4(aPos, 0.0, 1.0);\nTexCoord = aPos;\n}\n";
        const char* fragmentShaderSource = "#version 330 core\nout vec4 FragColor;\nuniform sampler2D sourceTexture;\nin vec2 TexCoord;\nvoid main()\n{\nFragColor = texture(sourceTexture, TexCoord);\n}\n";

// Compile the shaders
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

// Create a program and link the shaders
        unsigned int copyShaderProgram = glCreateProgram();
        glAttachShader(copyShaderProgram, vertexShader);
        glAttachShader(copyShaderProgram, fragmentShader);
        glLinkProgram(copyShaderProgram);

// Use the program
        glUseProgram(copyShaderProgram);

        texture0->Bind(0);
        glUniform1i(glGetUniformLocation(copyShaderProgram, "sourceTexture"), 0);

// Create a quad to render the texture to
        float copyVertices[] = {-1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f, -1.0f};
        unsigned int VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(copyVertices), copyVertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

// Render the quad
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
        glDrawArrays(GL_TRIANGLES, 0, 4);

// Cleanup
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(copyShaderProgram);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

    }

#endif

    renderer = CreateScope<Renderer>() ;
}

Test::TestTexture2D::~TestTexture2D() {
    vertexArray->Delete();
    vertexArray.reset();

    vertexBuffer->Delete();
    vertexBuffer.reset();

    indexBuffer->Delete();
    indexBuffer.reset();

    shaderProgram->Delete();
    shaderProgram.reset();

#if COPY_TEXTURE
    GLCall( glDeleteFramebuffers(1, &fbo) );
#endif

    renderer.reset();

#if TEXTURE_CONVERTER
    converter.reset();
    renderer.reset();
#endif
}

TEST_RETURN Test::TestTexture2D::OnUpdate(float deltaTime) {
    return TEST_RETURN_FAILURE;
}

TEST_RETURN Test::TestTexture2D::OnRender() {
    GLCall(glClearColor(1.f, 0.0f, 0.0f, 1.0));

    renderer->Clear() ;

#if TEXTURE_CONVERTER
    converter->convert(*texture0, *renderTexture);
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
    renderTexture->Bind(slot0);
#else
    texture0->Bind(slot0);
#endif
    shaderProgram->Bind();
    shaderProgram->setInt("u_Texture0", slot0);

    renderer->DrawElements(*vertexArray, *indexBuffer, *shaderProgram);

    return TEST_RETURN_SUCCESS;
}

TEST_RETURN Test::TestTexture2D::OnImGuiRender() {
    return TEST_RETURN_FAILURE;
}
