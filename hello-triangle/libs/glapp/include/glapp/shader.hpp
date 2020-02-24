#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>

class Shader {
  public:
    GLuint program;
    Shader(const char* vShaderPath, const char* fShaderPath); 
    ~Shader();
    void use();
  private:
    void linkShader(const char* vShaderPath, const char* fShaderPath);
    const GLuint compileSharder(const char* shaderpath, GLenum type); 
};

#endif