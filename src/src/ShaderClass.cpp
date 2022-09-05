//
// Created by Anshul Saraf on 30/08/22.
//

#include "ShaderClass.h"

// Reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const char* filename){
    std::ifstream in(filename, std::ios::binary);
    if (in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }
    throw(errno);
}

// Constructor that build the Shader Program from 2 different shaders
Shader::Shader(const char* vertexFile, const char* fragmentFile){

    // Read vertexFile and fragmentFile and store the strings
    std::string vertexCode = get_file_contents(vertexFile);
    std::string fragmentCode = get_file_contents(fragmentFile);

    // Convert the shader source strings into character arrays
    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    GLuint vertexShader = compileShaders(vertexSource, GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShaders(fragmentSource, GL_FRAGMENT_SHADER);

    // Create Shader Program Object and get its reference
    ID = glCreateProgram();
    // Attach the Vertex and Fragment Shaders to the Shader Program
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    // Wrap-up/Link all the shaders together into the Shader Program
    glLinkProgram(ID);
    // Checks if Shaders linked successfully
    compileErrors(ID, 0);

    // Delete the now useless Vertex and Fragment Shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}

// Activates the Shader Program
void Shader::Activate(){
    glUseProgram(ID);
}

// Deletes the Shader Program
void Shader::Delete(){
    glDeleteProgram(ID);
}

void Shader::setBool(const std::string &name, bool value){
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value){
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value){
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

// Checks if the different Shaders have compiled properly
void Shader::compileErrors(unsigned int shader, GLint type) {
    // Stores status of compilation
    GLint hasCompiled;
    // Character array to store error message in
    char infoLog[1024];
    if (type == GL_VERTEX_SHADER || type == GL_FRAGMENT_SHADER) {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
        if (hasCompiled == GL_FALSE) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "SHADER_COMPILATION_ERROR for:" << ((type == GL_VERTEX_SHADER) ? "Vertex Shader" : "Fragment Shader" ) << "\n" << infoLog << std::endl;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
        if (hasCompiled == GL_FALSE) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "SHADER_LINKING_ERROR for:" << "PROGRAM" << "\n" << infoLog << std::endl;
        }
    }
}

GLuint Shader::compileShaders(const char *source, GLint type) {
    // Create Shader Object and get its reference
    GLuint id = glCreateShader(type);
    // Attach Shader source to the Shader Object
    glShaderSource(id, 1, &source, nullptr);
    // Compile the Shader into machine code
    glCompileShader(id);
    // Checks if Shader compiled successfully
    compileErrors(id, type);
    return id;
}
