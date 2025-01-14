#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Render.h"

#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

// This example can also compile and run with Emscripten! See 'Makefile.emscripten' for details.
#ifdef __EMSCRIPTEN__
#include "../libs/emscripten/emscripten_mainloop_stub.h"
#endif

class GuiApplication
{
public:
    GuiApplication(const char* window_title, int width = 1200, int height = 900);
    ~GuiApplication();

    void Run();
 
private:
    GuiApplication(const GuiApplication&) = delete;
    GuiApplication& operator=(const GuiApplication&) = delete;

    bool Initialize();

    void CleaUp();

    void ProcessFrame();


public:

private:
    
    GLFWwindow* m_window = nullptr;

    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    ImGuiIO* m_io = nullptr;

    Renderer renderer;

    const char* m_window_title;
    int m_width, m_height;
};