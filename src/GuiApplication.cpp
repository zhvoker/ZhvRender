#include <stdio.h>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

#include "GuiApplication.h"

GuiApplication::GuiApplication(const char* window_title, int width, int height)
    : m_window_title(window_title), m_width(width), m_height(height)
    {

    }

GuiApplication::~GuiApplication(){    CleaUp(); }

bool GuiApplication::Initialize()
{
    // 设置错误回调函数
    glfwSetErrorCallback([](int error, const char* description){
        fprintf(stderr, "GLFW Error %d: %s\n", error, description);
    });

    //  创建日志记录器
    auto logger = spdlog::basic_logger_mt("file", "ZhvRender_Log.log");

    if(!glfwInit()) 
    {
        logger->critical("(glfw初始化失败)glfwInit failed！");
        return false;
    }

    const char* glsl_version = "#version 330 core";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only

    m_window = glfwCreateWindow(m_width, m_height, m_window_title, nullptr, nullptr);
    if(!m_window)
    {
        logger->critical("glfw 创建窗口失败(glfwCreateWindow failed!)");
        glfwTerminate();
        return false;
    }

    // 激活窗口上下文
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);

    // glad 初始化
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to init GLAD" << std::endl;
    }

    // 初始化ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    m_io = &ImGui::GetIO();
    m_io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableGamepad;     
    ImGui::StyleColorsDark();

    //初始化 Imgui
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    renderer.Initialize();

    return true;
}

// 清理资源
void GuiApplication::CleaUp()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    if(m_window != nullptr)
    {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }

    glfwTerminate();
}

void GuiApplication::Run()
{
    if(!Initialize()) 
        return;

#ifdef __EMSCRIPTEN__
    // For an Emscripten build we are disabling file-system access, so let's not attempt to do a fopen() of the imgui.ini file.
    // You may manually call LoadIniSettingsFromMemory() to load settings from your own storage.
    m_io->IniFilename = nullptr;
    EMSCRIPTEN_MAINLOOP_BEGIN
#else
    while (!glfwWindowShouldClose(m_window))
#endif
    {
        // 处理输入事件
        glfwPollEvents();
        if(glfwGetWindowAttrib(m_window, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            return;
        }
        
        ProcessFrame();
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_MAINLOOP_END;
#endif
}

void GuiApplication::ProcessFrame()
{
    // 新的渲染帧
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
    {
    
        ImGui::SetNextWindowSize(ImVec2(500, 500));
        ImGui::Begin("渲染界面");                          

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / m_io->Framerate, m_io->Framerate); 
        ImGui::End();
    }

    // 开启渲染
    ImGui::Render();
    // 获取屏幕帧缓冲区大小
    int display_w, display_h;
    glfwGetFramebufferSize(m_window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    // 设置背景颜色并设置
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    renderer.Render();
    
    // 切换缓冲区
    glfwSwapBuffers(m_window);
}