/**
 * @file GlobalContext.cpp
 * @author Kexuan Zhang (zzxzzk115@gmail.com)
 * @brief
 * @version 0.1.0
 * @date 2023-11-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "SomeEngineRuntime/Function/Global/GlobalContext.h"
#include "SomeEngineRuntime/Core/LoggerSystem.h"
#include "SomeEngineRuntime/Platform/Platform.h"

#if SOME_ENGINE_RENDER_API_OPENGL
#include "SomeEngineRuntime/Function/Rendering/Renderer/OpenGL/GL/OpenGLRenderSystem.h"
#elif SOME_ENGINE_RENDER_API_OPENGLES
#include "SomeEngineRuntime/Function/Rendering/Renderer/OpenGL/GLES/OpenGLESRenderSystem.h"
#endif

#if SOME_ENGINE_WINDOW_ABSTRACT_GLFW
#include "SomeEngineRuntime/Platform/WindowAbstract/GLFW/GLFWWindowSystem.h"
#elif SOME_ENGINE_WINDOW_ABSTRACT_SDL
#include "SomeEngineRuntime/Platform/WindowAbstract/SDL/SDLWindowSystem.h"
#elif SOME_ENGINE_WINDOW_ABSTRACT_EGL
#include "SomeEngineRuntime/Platform/WindowAbstract/EGL/EGLWindowSystem.h"
#endif

#if SOME_ENGINE_GUI_IMPL_IMGUI
#include "SomeEngineRuntime/Function/GUI/ImGui/ImGuiGUISystem.h"
#endif

#if SOME_ENGINE_PLATFORM_ANDROID
#include <game-activity/native_app_glue/android_native_app_glue.h>
#endif

namespace SomeEngineRuntime
{
    RuntimeGlobalContext g_RuntimeGlobalContext;

    void RuntimeGlobalContext::StartSystems(RuntimeGlobalContextInitInfo initInfo)
    {
#if SOME_ENGINE_PLATFORM_ANDROID
        NativeApp = static_cast<struct android_app*>(initInfo.NativeApp);
#else
        NativeApp = nullptr;
#endif

        LoggerSys = CreateRef<LoggerSystem>();
#if SOME_ENGINE_WINDOW_ABSTRACT_GLFW
        WindowSys = CreateRef<GLFWWindowSystem>();
#elif SOME_ENGINE_WINDOW_ABSTRACT_SDL
        WindowSys = CreateRef<SDLWindowSystem>();
#elif SOME_ENGINE_WINDOW_ABSTRACT_EGL
        WindowSys = CreateRef<EGLWindowSystem>();
#endif
        WindowSystemInitInfo windowSystemInitInfo = {};
        windowSystemInitInfo.Title                = initInfo.AppName;
        windowSystemInitInfo.Width                = initInfo.WindowWidth;
        windowSystemInitInfo.Height               = initInfo.WindowHeight;
        WindowSys->Init(windowSystemInitInfo);

#if SOME_ENGINE_RENDER_API_OPENGL
        RenderSys = CreateRef<OpenGLRenderSystem>();
#elif SOME_ENGINE_RENDER_API_OPENGLES
        RenderSys = CreateRef<OpenGLESRenderSystem>();
#endif
        RenderSystemInitInfo renderSystemInitInfo = {};
        renderSystemInitInfo.WindowSys            = WindowSys;
        RenderSys->Init(renderSystemInitInfo);

#if SOME_ENGINE_GUI_IMPL_IMGUI
        GUISys = CreateRef<ImGuiGUISystem>();
#endif
        GUISystemInitInfo guiSystemInitInfo = {};
        guiSystemInitInfo.WindowSys         = WindowSys;
        GUISys->Init(guiSystemInitInfo);
    }

    void RuntimeGlobalContext::ShutdownSystems()
    {
        GUISys->Shutdown();
        GUISys.reset();

        RenderSys->Shutdown();
        RenderSys.reset();

        WindowSys->Shutdown();
        WindowSys.reset();

        LoggerSys.reset();
    }
} // namespace SomeEngineRuntime
