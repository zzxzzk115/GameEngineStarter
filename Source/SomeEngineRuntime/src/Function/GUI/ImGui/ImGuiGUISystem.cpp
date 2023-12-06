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
#include "SomeEngineRuntime/Core/Event/SDL2Event.h"
#include "SomeEngineRuntime/Platform/WindowAbstract/SDL/SDLWindowSystem.h"
#include <imgui_impl_sdl2.h>
#elif SOME_ENGINE_WINDOW_ABSTRACT_EGL
#include "SomeEngineRuntime/Core/Event/MouseEvent.h"
#include "SomeEngineRuntime/Platform/WindowAbstract/EGL/EGLWindowSystem.h"
#include <imgui_impl_android.h>
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

        // if on Android, set scale
#if SOME_ENGINE_WINDOW_ABSTRACT_EGL && SOME_ENGINE_PLATFORM_ANDROID
        // We load the default font with increased size to improve readability on many devices with "high" DPI.
        // FIXME: Put some effort into DPI awareness.
        // Important: when calling AddFontFromMemoryTTF(), ownership of font_data is transfered by Dear ImGui by default
        // (deleted is handled by Dear ImGui), unless we set FontDataOwnedByAtlas=false in ImFontConfig
        ImFontConfig font_cfg;
        font_cfg.SizePixels = 22.0f;
        io.Fonts->AddFontDefault(&font_cfg);
        // void* font_data;
        // int font_data_size;
        // ImFont* font;
        // font_data_size = GetAssetData("segoeui.ttf", &font_data);
        // font = io.Fonts->AddFontFromMemoryTTF(font_data, font_data_size, 16.0f);
        // IM_ASSERT(font != nullptr);
        // font_data_size = GetAssetData("DroidSans.ttf", &font_data);
        // font = io.Fonts->AddFontFromMemoryTTF(font_data, font_data_size, 16.0f);
        // IM_ASSERT(font != nullptr);
        // font_data_size = GetAssetData("Roboto-Medium.ttf", &font_data);
        // font = io.Fonts->AddFontFromMemoryTTF(font_data, font_data_size, 16.0f);
        // IM_ASSERT(font != nullptr);
        // font_data_size = GetAssetData("Cousine-Regular.ttf", &font_data);
        // font = io.Fonts->AddFontFromMemoryTTF(font_data, font_data_size, 15.0f);
        // IM_ASSERT(font != nullptr);
        // font_data_size = GetAssetData("ArialUni.ttf", &font_data);
        // font = io.Fonts->AddFontFromMemoryTTF(font_data, font_data_size, 18.0f, nullptr,
        // io.Fonts->GetGlyphRangesJapanese()); IM_ASSERT(font != nullptr);

        // Arbitrary scale-up
        // FIXME: Put some effort into DPI awareness
        ImGui::GetStyle().ScaleAllSizes(3.0f);
#endif

        // SetDarkThemeColors(); // you can set your own colors.

        // Setup Platform/Renderer bindings
#if SOME_ENGINE_WINDOW_ABSTRACT_GLFW
        ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)m_WindowSys->GetWindow(), true);
#elif SOME_ENGINE_WINDOW_ABSTRACT_SDL
        ImGui_ImplSDL2_InitForOpenGL((SDL_Window*)m_WindowSys->GetWindow(), SDL_GL_GetCurrentContext());
#elif SOME_ENGINE_WINDOW_ABSTRACT_EGL && SOME_ENGINE_PLATFORM_ANDROID
        ImGui_ImplAndroid_Init((ANativeWindow*)m_WindowSys->GetNativeWindow());
#endif

#if SOME_ENGINE_RENDER_API_OPENGL
        ImGui_ImplOpenGL3_Init("#version 330");
#elif SOME_ENGINE_RENDER_API_OPENGLES
        ImGui_ImplOpenGL3_Init("#version 100");
#endif

        SOME_ENGINE_CORE_INFO("[ImGuiGUISystem] Initialized");
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
#elif SOME_ENGINE_WINDOW_ABSTRACT_EGL && SOME_ENGINE_PLATFORM_ANDROID
        ImGui_ImplAndroid_Shutdown();
#endif
        ImGui::DestroyContext();
    }

    void ImGuiGUISystem::Update(float deltaTime)
    {
        // TODO: test only, remove
#if SOME_ENGINE_WINDOW_ABSTRACT_EGL && SOME_ENGINE_PLATFORM_ANDROID
        ImGui::ShowDemoWindow();

        ImGui::Begin("SomeEngineDebugWindow");
        ImGui::Text("Hello, SomeEngine!");
        ImGui::End();
#endif
    }

    void ImGuiGUISystem::OnEvent(Event& e)
    {
        // handle for SDL2 events
#if SOME_ENGINE_WINDOW_ABSTRACT_SDL
        if (e.GetEventType() == EventType::SDL2Event)
        {
            auto sdl2Event = static_cast<SDL2Event&>(e);
            ImGui_ImplSDL2_ProcessEvent(sdl2Event.Get());
            e.Handled = true;
            return;
        }
#elif SOME_ENGINE_WINDOW_ABSTRACT_EGL
        ImGuiIO& io = ImGui::GetIO();

        // MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
        switch (e.GetEventType())
        {
            case EventType::MouseButtonPressed: {
                io.AddMouseButtonEvent(0, true);
            }
            break;
            case EventType::MouseButtonReleased: {
                io.AddMouseButtonEvent(0, false);
            }
            break;
            case EventType::MouseMoved: {
                auto mouseMovedEvent = static_cast<MouseMovedEvent&>(e);
                io.AddMousePosEvent(mouseMovedEvent.GetX(), mouseMovedEvent.GetY());
            }
            break;
            default:
                break;
        }
#endif
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
#elif SOME_ENGINE_WINDOW_ABSTRACT_EGL && SOME_ENGINE_PLATFORM_ANDROID
        ImGui_ImplAndroid_NewFrame();
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
