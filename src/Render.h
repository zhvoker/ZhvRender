#pragma once

#include <memory>
#include "Shader.h"

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
    unsigned int VAO, VBO, EBO;
    unsigned int m_shader_program;

    unsigned int texture1, texture2;

    std::unique_ptr<Shader> m_shader = nullptr;
};
