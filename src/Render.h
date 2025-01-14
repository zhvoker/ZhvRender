#include <GL/glew.h>

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void Initiaize();

    void Render();

private:
    void CleanUp();

private:
    GLuint VAO, VBO, EBO;
    GLuint m_shader_program;
};