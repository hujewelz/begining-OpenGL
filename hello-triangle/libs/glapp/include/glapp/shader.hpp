#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>


class Shader {
  public:
    GLuint program;
    Shader(const char* vertShader, const char* fragShader); 
    void use();
    ~Shader();
  private:
    void linkShader(const char* vertShader, const char* fragShader);
    const GLuint compileSharder(const char* shaderpath, GLenum type); 
};

#endif