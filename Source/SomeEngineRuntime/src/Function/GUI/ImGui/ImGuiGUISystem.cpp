/**
 * @file ImGuiGUISystem.cpp
 * @author Kexuan Zhang (zzxzzk115@gmail.com)
 * @brief
 * @version 0.1.0
 * @date 2023-11-28
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "SomeEngineRuntime/Function/GUI/ImGui/ImGuiGUISystem.h"
#include "SomeEngineRuntime/Platform/Platform.h"

#include <imgui.h>
#if SOME_ENGINE_WINDOW_ABSTRACT_GLFW
#include "SomeEngineRuntime/Platform/WindowAbstract/GLFW/GLFWWindowSystem.h"
#include <imgui_impl_glfw.h>
#elif SOME_ENGINE_WINDOW_ABSTRACT_SDL
#include "SomeEngineRuntime/Platform/WindowAbstract/SDL/SDLWindowSystem.h"
#include <imgui_impl_sdl2.h>
#endif
#if SOME_ENGINE_RENDER_API_OPENGL || SOME_ENGINE_RENDER_API_OPENGLES
#include <imgui_impl_opengl3.h>
#endif

namespace SomeEngineRuntime
{
    void ImGuiGUISystem::Init(const GUISystemInitInfo& initInfo)
    {
        m_WindowSys = initInfo.WindowSys;

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport
        // io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
        // io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

        ImGui::StyleColorsDark();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular
        // ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding              = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
            style.PopupRounding = style.TabRounding = 6.0f;
        }

        // SetDarkThemeColors(); // you can set your own colors.

        // Setup Platform/Renderer bindings
#if SOME_ENGINE_WINDOW_ABSTRACT_GLFW
        ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)m_WindowSys->GetWindow(), true);
#elif SOME_ENGINE_WINDOW_ABSTRACT_SDL
        ImGui_ImplSDL2_InitForOpenGL((SDL_Window*)m_WindowSys->GetWindow(), SDL_GL_GetCurrentContext());
#endif
#if SOME_ENGINE_RENDER_API_OPENGL
        ImGui_ImplOpenGL3_Init("#version 330");
#elif SOME_ENGINE_RENDER_API_OPENGLES
        ImGui_ImplOpenGL3_Init("#version 100");
#endif
    }

    void ImGuiGUISystem::Shutdown()
    {
#if SOME_ENGINE_RENDER_API_OPENGL || SOME_ENGINE_RENDER_API_OPENGLES
        ImGui_ImplOpenGL3_Shutdown();
#endif
#if SOME_ENGINE_WINDOW_ABSTRACT_GLFW
        ImGui_ImplGlfw_Shutdown();
#elif SOME_ENGINE_WINDOW_ABSTRACT_SDL
        ImGui_ImplSDL2_Shutdown();
#endif
        ImGui::DestroyContext();
    }

    void ImGuiGUISystem::Update(float deltaTime) {}

    void ImGuiGUISystem::OnEvent(Event& e)
    {
        if (m_IsBlockEvents)
        {
            ImGuiIO& io = ImGui::GetIO();
            e.Handled |= e.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
            e.Handled |= e.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
        }
    }

    void ImGuiGUISystem::Begin()
    {
#if SOME_ENGINE_RENDER_API_OPENGL || SOME_ENGINE_RENDER_API_OPENGLES
        ImGui_ImplOpenGL3_NewFrame();
#endif
#if SOME_ENGINE_WINDOW_ABSTRACT_GLFW
        ImGui_ImplGlfw_NewFrame();
#elif SOME_ENGINE_WINDOW_ABSTRACT_SDL
        ImGui_ImplSDL2_NewFrame();
#endif
        ImGui::NewFrame();
    }

    void ImGuiGUISystem::End()
    {
        ImGuiIO& io    = ImGui::GetIO();
        io.DisplaySize = ImVec2(m_WindowSys->GetWidth(), m_WindowSys->GetHeight());

        // Rendering
        ImGui::Render();
#if SOME_ENGINE_RENDER_API_OPENGL || SOME_ENGINE_RENDER_API_OPENGLES
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
#if SOME_ENGINE_RENDER_API_OPENGL || SOME_ENGINE_RENDER_API_OPENGLES
#if SOME_ENGINE_WINDOW_ABSTRACT_GLFW
            GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
#elif SOME_ENGINE_WINDOW_ABSTRACT_SDL
            SDL_Window*   window               = SDL_GL_GetCurrentWindow();
            SDL_GLContext backupCurrentContext = SDL_GL_GetCurrentContext();
#endif
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
#if SOME_ENGINE_WINDOW_ABSTRACT_GLFW
            glfwMakeContextCurrent(backupCurrentContext);
#elif SOME_ENGINE_WINDOW_ABSTRACT_SDL
            SDL_GL_MakeCurrent(window, backupCurrentContext);
#endif
#endif
        }
    }
} // namespace SomeEngineRuntime
