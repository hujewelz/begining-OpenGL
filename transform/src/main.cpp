#include <iostream>
#include <glapp/shader.hpp>
#include <glapp/glapp.hpp>
#include <image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

struct VertextData {
    GLfloat vertices[3];
    GLfloat colors[3];
    GLfloat texCoords[3];
};

enum VertextAttribIndex {
   VertextAttribPositionIndex,
   VertextAttribColorIndex,
   VertextAttribTexCoordIndex 
};

class MyApp: public GLApplication
{
private:
    GLuint VAO, VBO, texture;
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
            // 顶点坐标              颜色                 纹理坐标 
            {{-1.0f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},   // left bottom
            {{1.0f, -0.5f, 0.0f},  {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},   // right bottom
            {{1.0f, 0.5f, 0.0f},   {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},    // right top
            {{-1.0f, 0.5f, 0.0f},  {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},   // left top
        };

        // static const GLbyte indices[] = {
        //     0, 1, 2,
        //     0, 2, 3
        // };
        
        shader = new Shader("./resource/core.vs", "./resource/core.fs");

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // GLuint elementsBuffer;
        // glGenBuffers(1, &elementsBuffer);
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementsBuffer);
        // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(VertextAttribPositionIndex, 3, GL_FLOAT, GL_FALSE, sizeof(VertextData), (void *)(offsetof(VertextData, vertices)));
        glEnableVertexAttribArray(VertextAttribPositionIndex);
        glVertexAttribPointer(VertextAttribColorIndex, 3, GL_FLOAT, GL_FALSE, sizeof(VertextData), (void *)(offsetof(VertextData, colors)));
        glEnableVertexAttribArray(VertextAttribColorIndex);
        glVertexAttribPointer(VertextAttribTexCoordIndex, 2, GL_FLOAT, GL_FALSE, sizeof(VertextData), (void *)(offsetof(VertextData, texCoords)));
        glEnableVertexAttribArray(VertextAttribTexCoordIndex);

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width, height, channels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load("./resource/demo.jpg", &width, &height, &channels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_RECTANGLE);
        }
        stbi_image_free(data);


        glm::mat4 trans = glm::mat4(1.0f);
        // 每个轴都缩放到0.5倍，然后沿z轴旋转90度
        trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
        trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
        shader->use();
        GLint transformLoc = glGetUniformLocation(shader->program, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
    }

    void render() override
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // use program
        shader->use();

        glBindVertexArray(VAO);
        glBindTexture(GL_TEXTURE_2D, texture);

        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }
};

int main() {
    MyApp app("Transform", SCR_WIDTH, SCR_HEIGHT);
    app.run();
    return 0;
}