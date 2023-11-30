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

#include <glad/glad.h>
#include <string>

namespace SomeEngineRuntime
{
    void OpenGLContextBase::Init(Ref<WindowSystem> windowSys)
    {
        std::string tag = "[" + GetName() + "Context]";
#if SOME_ENGINE_WINDOW_ABSTRACT_GLFW
        m_Window = (GLFWwindow*)windowSys->GetWindow();
        glfwMakeContextCurrent(m_Window);
        int version = LoadGL();
#elif SOME_ENGINE_WINDOW_ABSTRACT_SDL
        m_Window                = (SDL_Window*)windowSys->GetWindow();
        SDL_GLContext glContext = SDL_GL_CreateContext(m_Window);
        SOME_ENGINE_CORE_ASSERT(!glContext, tag + " Failed to create SDL GL Context!");
        SDL_GL_MakeCurrent(m_Window, glContext);
        int version = LoadGL();
#endif
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
#if SOME_ENGINE_WINDOW_ABSTRACT_GLFW
        glfwSwapBuffers(m_Window);
#elif SOME_ENGINE_WINDOW_ABSTRACT_SDL
        SDL_GL_SwapWindow(m_Window);
#endif
    }

    void OpenGLContextBase::SetVSync(bool vsyncEnabled)
    {
#if SOME_ENGINE_WINDOW_ABSTRACT_GLFW
        glfwSwapInterval(vsyncEnabled);
#elif SOME_ENGINE_WINDOW_ABSTRACT_SDL
        SDL_GL_SetSwapInterval(vsyncEnabled);
#endif
    }
} // namespace SomeEngineRuntime
