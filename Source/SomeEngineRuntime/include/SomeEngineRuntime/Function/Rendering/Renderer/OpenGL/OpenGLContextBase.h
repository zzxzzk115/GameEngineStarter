/**
 * @file OpenGLContextBase.h
 * @author Kexuan Zhang (zzxzzk115@gmail.com)
 * @brief
 * @version 0.1.0
 * @date 2023-11-29
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include "SomeEngineRuntime/Core/Base.h"
#include "SomeEngineRuntime/Platform/Platform.h"
#if SOME_ENGINE_WINDOW_ABSTRACT_GLFW
#include "SomeEngineRuntime/Platform/WindowAbstract/GLFW/GLFWWindowSystem.h"
#elif SOME_ENGINE_WINDOW_ABSTRACT_SDL
#include "SomeEngineRuntime/Platform/WindowAbstract/SDL/SDLWindowSystem.h"
#endif

#include <string>

namespace SomeEngineRuntime
{
    class WindowSystem;

    class OpenGLContextBase
    {
    public:
        virtual void Init(Ref<WindowSystem> windowSys);
        virtual void Shutdown();

        virtual void SwapBuffers();
        virtual void SetVSync(bool vsyncEnabled);

        virtual int                LoadGL()      = 0;
        virtual int                GetMinMajor() = 0;
        virtual int                GetMinMinor() = 0;
        virtual const std::string& GetName()     = 0;

    protected:
#if SOME_ENGINE_WINDOW_ABSTRACT_GLFW
        GLFWwindow* m_Window;
#elif SOME_ENGINE_WINDOW_ABSTRACT_SDL
        SDL_Window* m_Window;
#endif
    };
} // namespace SomeEngineRuntime
