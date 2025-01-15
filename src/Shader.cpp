#include "Shader.h"

Shader::Shader(const GLchar* vertex_path, const GLchar* fragment_path)
{
    std::string vertex_code;
    std::string fragment_code;
    std::ifstream vertex_shader_file;
    std::ifstream fragment_shader_file;

    // 确保 ifstream 可抛出异常
    vertex_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragment_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        // 打开文件
        vertex_shader_file.open(vertex_path);
        fragment_shader_file.open(fragment_path);
        // 读取文件流
        std::stringstream vertex_shader_stream, fragment_shader_stream;
        vertex_shader_stream << vertex_shader_file.rdbuf();
        fragment_shader_stream << fragment_shader_file.rdbuf();
        // 关闭文件
        vertex_shader_file.close();
        fragment_shader_file.close();
        // 获取shader代码
        vertex_code = vertex_shader_stream.str();
        fragment_code = vertex_shader_stream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << e.what() << std::endl;
    }
    // 获取c字符串
    const char* vertex_shader_code = vertex_code.c_str();
    const char* fragment_shader_code = fragment_code.c_str();
    //编译
    unsigned int vertex, fragment;
    //顶点着色器
    vertex = glCreateShader(GL_VERTEX_SHADER);               // 创建顶点着色器
    glShaderSource(vertex, 1, &vertex_shader_code, NULL);    // 绑定vshader 和vshader 代码
    glCompileShader(vertex);                                 // 编译vshader

    checkCompileErrors(vertex, "VERTEX");

    //片段着色器
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragment_shader_code, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    //着色器程序
    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertex);
    glAttachShader(m_ID, fragment);
    glLinkProgram(m_ID);
    checkCompileErrors(m_ID, "PROGRAMG");

    // 释放着色器
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader(){}

void Shader::Use()
{
    glUseProgram(m_ID);
}


