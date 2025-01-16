#pragma once 

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

class Shader
{
public:
    Shader(const char* vertex_path, const char* fragment_path);
    ~Shader();

    void Use();

    void SetBool(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
    }

    void SetInt(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
    }

    void SetFloat(const std::string &name, float value) const
    {
        glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
    }

    unsigned int GetID() const
    {
        return m_ID;
    }

private:
    void checkCompileErrors(unsigned int shader, std::string type)
    {
        int success = 1;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }


private:
    unsigned int m_ID;
};
