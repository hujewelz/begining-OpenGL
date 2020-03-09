#include <glapp/shader.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vShaderPath, const char* fShaderPath) 
{
    linkShader(vShaderPath, fShaderPath);
}

void Shader::use() 
{
    glUseProgram(program);
}

Shader::~Shader() 
{
    glDeleteProgram(program);
}

void Shader::linkShader(const char* vShaderPath, const char* fShaderPath) 
{
    program = glCreateProgram();
    GLuint vertexShader = compileSharder(vShaderPath, GL_VERTEX_SHADER);
    GLuint fragmentShader = compileSharder(fShaderPath, GL_FRAGMENT_SHADER);
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    
    glLinkProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

const GLuint Shader::compileSharder(const char* shaderpath, GLenum type) 
{
    std::string sCode;
    std::ifstream shaderFile;
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::cout << "SHAPER PATH:" << shaderpath << std::endl;
    try {
        // open the file
        shaderFile.open(shaderpath);
        std::stringstream shaderStream;
        // read file buffer to stream
        shaderStream << shaderFile.rdbuf();
        // close file
        shaderFile.close();
        sCode = shaderStream.str();
    } catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    const char* shaderSource = sCode.c_str();
    GLuint shader;
    shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar info[255];
        glGetShaderInfoLog(shader, 255, NULL, &info[0]);

        std::cout << (type == GL_VERTEX_SHADER ? "Vertex Shader" : "Fragment Shader") << "compile with error: " << info << std::endl;
    }
    return shader;
} 