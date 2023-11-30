#include "SomeEngineRuntime/Core/Application.h"
/**
 * @file Application.cpp
 * @author Kexuan Zhang (zzxzzk115@gmail.com)
 * @brief
 * @version 0.1.0
 * @date 2023-11-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "SomeEngineRuntime/Core/LoggerSystem.h"
#include "SomeEngineRuntime/Core/Macro.h"
#include "SomeEngineRuntime/Function/Global/GlobalContext.h"
#if SOME_ENGINE_RENDER_API_OPENGL
#include "SomeEngineRuntime/Function/Rendering/Renderer/OpenGL/GL/OpenGLRenderSystem.h"
#elif SOME_ENGINE_RENDER_API_OPENGLES
#include "SomeEngineRuntime/Function/Rendering/Renderer/OpenGL/GLES/OpenGLESRenderSystem.h"
#endif
#if SOME_ENGINE_WINDOW_ABSTRACT_GLFW
#include "SomeEngineRuntime/Platform/WindowAbstract/GLFW/GLFWWindowSystem.h"
#elif SOME_ENGINE_WINDOW_ABSTRACT_SDL
#include "SomeEngineRuntime/Platform/WindowAbstract/SDL/SDLWindowSystem.h"
#endif
#if SOME_ENGINE_GUI_IMPL_IMGUI
#include "SomeEngineRuntime/Function/GUI/ImGui/ImGuiGUISystem.h"
#endif

namespace SomeEngineRuntime
{
    Application::Application(const ApplicationArgs& args) : m_InitArgs(args)
    {
        // init runtime global context
        RuntimeGlobalContextInitInfo runtimeGlobalContextInitInfo = {};
        runtimeGlobalContextInitInfo.AppName                      = args.Name;
        runtimeGlobalContextInitInfo.WindowWidth                  = args.WindowWidth;
        runtimeGlobalContextInitInfo.WindowHeight                 = args.WindowHeight;
        g_RuntimeGlobalContext.StartSystems(runtimeGlobalContextInitInfo);

        SOME_ENGINE_CORE_INFO("[Application] Initializing...");

        // bind window events
        g_RuntimeGlobalContext.WindowSys->SetEventCallback(SOME_ENGINE_BIND_EVENT_FN(Application::OnEvent));

        SOME_ENGINE_CORE_INFO("[Application] Initialized");
    }

    Application::~Application()
    {
        SOME_ENGINE_CORE_INFO("[Application] Shutting down...");
        m_CustomModuleManager.Shutdown();
        g_RuntimeGlobalContext.ShutdownSystems();
    }

    void Application::Run()
    {
        SOME_ENGINE_CORE_INFO("[Application] Running...");

        while (m_IsRunning)
        {
            // calculate delta time by using std::chrono
            auto currentTime = std::chrono::high_resolution_clock::now();
            auto deltaTime   = std::chrono::duration<float>(currentTime - m_LastFrameTime).count();
            m_LastFrameTime  = currentTime;

            // update window system
            if (!g_RuntimeGlobalContext.WindowSys->OnUpdate())
            {
                break;
            }

            if (!m_IsMinimized)
            {
                // update custom modules
                m_CustomModuleManager.ForEach([deltaTime](Ref<CustomModule> module) { module->OnUpdate(deltaTime); });

                // update render system
                g_RuntimeGlobalContext.RenderSys->Update(deltaTime);
                
                // update GUI system
                g_RuntimeGlobalContext.GUISys->Begin();
                g_RuntimeGlobalContext.GUISys->Update(deltaTime);
                m_CustomModuleManager.ForEach([deltaTime](Ref<CustomModule> module) { module->OnGUI(); });
                g_RuntimeGlobalContext.GUISys->End();
            }

            // render present
            g_RuntimeGlobalContext.RenderSys->Present();
        }

        SOME_ENGINE_CORE_INFO("[Application] Exited main loop");
    }

    void Application::Quit() { m_IsRunning = false; }

    void Application::OnEvent(Event& e)
    {
        // dispatch event
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(SOME_ENGINE_BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(SOME_ENGINE_BIND_EVENT_FN(Application::OnWindowResize));

        m_CustomModuleManager.ForEachIf([&e](Ref<CustomModule> module) { module->OnEvent(e); },
                                        [&e](Ref<CustomModule> module) { return !e.Handled; });
    }

    void Application::AddCustomModule(Ref<CustomModule> module)
    {
        m_CustomModuleManager.AddModule(module);
        module->OnInit();
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_IsRunning = false;
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent& e)
    {
        auto w = e.GetWidth();
        auto h = e.GetHeight();

        if (w == 0 || h == 0)
        {
            m_IsMinimized = true;
            return false;
        }

        m_IsMinimized = false;
        g_RuntimeGlobalContext.RenderSys->SetViewport(0, 0, w, h);

        return false;
    }
} // namespace SomeEngineRuntime