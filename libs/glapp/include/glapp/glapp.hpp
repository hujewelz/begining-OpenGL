#ifndef __GLAPP_H__
#define __GLAPP_H__ 
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

class GLApplication
{
public:
    void run();
    virtual void initialized() {};
    virtual void render() {};
    void processInput(GLFWwindow *window);
private:
    bool isInitialized = false;
    void initial(); 
    // void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};
#endif