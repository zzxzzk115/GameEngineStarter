/**
 * @file OpenGLESContext.cpp
 * @author Kexuan Zhang (zzxzzk115@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-11-29
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "SomeEngineRuntime/Function/Rendering/Renderer/OpenGL/GLES/OpenGLESContext.h"

#include <glad/glad.h>

namespace SomeEngineRuntime
{
    int OpenGLESContext::LoadGL()
    {
#if SOME_ENGINE_WINDOW_ABSTRACT_GLFW
        return gladLoadGLES2Loader((GLADloadproc)glfwGetProcAddress);
#elif SOME_ENGINE_WINDOW_ABSTRACT_SDL
        return gladLoadGLES2Loader((GLADloadproc)SDL_GL_GetProcAddress);
#endif
    }
} // namespace SomeEngineRuntime
