/**
 * @file OpenGLContextBase.cpp
 * @author Kexuan Zhang (zzxzzk115@gmail.com)
 * @brief
 * @version 0.1.0
 * @date 2023-11-29
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "SomeEngineRuntime/Function/Rendering/Renderer/OpenGL/OpenGLContextBase.h"
#include "SomeEngineRuntime/Platform/Platform.h"
#if SOME_ENGINE_WINDOW_ABSTRACT_GLFW
#include "SomeEngineRuntime/Platform/WindowAbstract/GLFW/GLFWWindowSystem.h"
#elif SOME_ENGINE_WINDOW_ABSTRACT_SDL
#include "SomeEngineRuntime/Platform/WindowAbstract/SDL/SDLWindowSystem.h"
#elif SOME_ENGINE_WINDOW_ABSTRACT_EGL
#include "SomeEngineRuntime/Platform/WindowAbstract/EGL/EGLWindowSystem.h"
#endif

#include <glad/glad.h>
#include <string>

namespace SomeEngineRuntime
{
    void OpenGLContextBase::Init(Ref<WindowSystem> windowSys)
    {
        std::string tag = "[" + GetName() + "Context]";

        m_WindowSys = windowSys;
        m_WindowSys->MakeCurrentContext();
        int version = LoadGL();

        SOME_ENGINE_CORE_ASSERT(version, tag + " Failed to initialize Glad!");
        if (version)
        {
            auto glName   = GetName();
            int  minMajor = GetMinMajor();
            int  minMinor = GetMinMinor();
            SOME_ENGINE_CORE_INFO("[{0}Context] Loaded {1} {2}.{3}", glName, glName, GLVersion.major, GLVersion.minor);
            SOME_ENGINE_CORE_ASSERT(GLVersion.major > minMajor || (GLVersion.major == minMajor && GLVersion.minor >= minMinor),
                            tag + " SomeEngine requires at least " + glName + " version " +
                                std::to_string(minMajor) + "." +
                                std::to_string(minMinor));
        }
    }

    void OpenGLContextBase::Shutdown()
    {
#if SOME_ENGINE_WINDOW_ABSTRACT_SDL
        SDL_GL_DeleteContext(SDL_GL_GetCurrentContext());
#endif
    }

    void OpenGLContextBase::SwapBuffers()
    {
        m_WindowSys->SwapBuffers();
    }

    void OpenGLContextBase::SetVSync(bool vsyncEnabled)
    {
#if SOME_ENGINE_WINDOW_ABSTRACT_GLFW
        glfwSwapInterval(vsyncEnabled);
#elif SOME_ENGINE_WINDOW_ABSTRACT_SDL
        SDL_GL_SetSwapInterval(vsyncEnabled);
#elif SOME_ENGINE_WINDOW_ABSTRACT_EGL
        eglSwapInterval(m_WindowSys->GetWindow(), vsyncEnabled);
#endif
    }
} // namespace SomeEngineRuntime
