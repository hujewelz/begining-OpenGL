#ifndef GLAPP_H
#define GLAPP_H 
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLApplication
{
public:
    GLApplication(const char* title, int screenWidth, int screenHeight) : m_title(title), m_screenWidth(screenWidth), m_screenHeight(screenHeight) {};
    void run();
    virtual void initialized() {};
    virtual void render() {};
    void processInput(GLFWwindow *window);
private:
    const char* m_title;
    int m_screenWidth, m_screenHeight;
    bool isInitialized = false;
    void initial(); 
    // void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};
#endif