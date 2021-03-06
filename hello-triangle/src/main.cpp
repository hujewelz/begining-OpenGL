#include <iostream>
#include <glapp/shader.hpp>
#include <glapp/glapp.hpp>

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

struct VertextData {
    GLfloat vertices[3];
    GLfloat colors[3];
};

enum VertextAttribIndex {
   VertextAttribPositionIndex,
   VertextAttribColorIndex 
};

class MyApp: public GLApplication
{
private:
    GLuint VAO, VBO;
    Shader *shader;
public:
    MyApp(const char* title, int screenWidth, int screenHeight) : GLApplication(title, screenWidth, screenHeight) {}

    ~MyApp()
    {
        delete shader;
    }

    void initialized() override
    {
        static const VertextData vertices[] = {
            {{-1.0f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},  // left bottom
            {{1.0f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},   // right bottom
            {{0.0f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},    // middle top
        };
        
        shader = new Shader("./resource/core.vs", "./resource/core.fs");

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(VertextAttribPositionIndex, 3, GL_FLOAT, GL_FALSE, sizeof(VertextData), (void *)(offsetof(VertextData, vertices)));
        glEnableVertexAttribArray(VertextAttribPositionIndex);
        glVertexAttribPointer(VertextAttribColorIndex, 3, GL_FLOAT, GL_FALSE, sizeof(VertextData), (void *)(offsetof(VertextData, colors)));
        glEnableVertexAttribArray(VertextAttribColorIndex);
    }

    void render() override
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // use program
        shader->use();

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
};

int main() {
    MyApp app("HellTriangle", SCR_WIDTH, SCR_HEIGHT);
    app.run();
    return 0;
}