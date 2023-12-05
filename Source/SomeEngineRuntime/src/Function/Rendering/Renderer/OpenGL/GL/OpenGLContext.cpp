/**
 * @file OpenGLContext.cpp
 * @author Kexuan Zhang (zzxzzk115@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-11-28
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "SomeEngineRuntime/Function/Rendering/Renderer/OpenGL/GL/OpenGLContext.h"

#if SOME_ENGINE_WINDOW_ABSTRACT_GLFW
#include <GLFW/glfw3.h>
#elif SOME_ENGINE_WINDOW_ABSTRACT_SDL
#include <SDL.h>
#elif SOME_ENGINE_WINDOW_ABSTRACT_EGL
#include <EGL/egl.h>
#endif

#include <glad/glad.h>

namespace SomeEngineRuntime
{
    int OpenGLContext::LoadGL()
    {
#if SOME_ENGINE_WINDOW_ABSTRACT_GLFW
        return gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
#elif SOME_ENGINE_WINDOW_ABSTRACT_SDL
        return gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
#elif SOME_ENGINE_WINDOW_ABSTRACT_EGL
        return gladLoadGLES2Loader((GLADloadproc)eglGetProcAddress);
#endif
    }
} // namespace SomeEngineRuntime
