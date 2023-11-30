/**
 * @file OpenGLRenderSystemBase.cpp
 * @author Kexuan Zhang (zzxzzk115@gmail.com)
 * @brief 
 * @version 0.1.0
 * @date 2023-11-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "SomeEngineRuntime/Function/Rendering/Renderer/OpenGL/OpenGLRenderSystemBase.h"
#include "SomeEngineRuntime/Platform/Platform.h"
#if SOME_ENGINE_WINDOW_ABSTRACT_GLFW
#include "SomeEngineRuntime/Platform/WindowAbstract/GLFW/GLFWWindowSystem.h"
#endif
#if SOME_ENGINE_RENDER_API_OPENGL
#include "SomeEngineRuntime/Function/Rendering/Renderer/OpenGL/GL/OpenGLContext.h"
#elif SOME_ENGINE_RENDER_API_OPENGLES
#include "SomeEngineRuntime/Function/Rendering/Renderer/OpenGL/GLES/OpenGLESContext.h"
#endif

#include <glad/glad.h>

namespace SomeEngineRuntime
{
    void OpenGLRenderSystemBase::Init(const RenderSystemInitInfo& initInfo)
    {
        // 1. Create OpenGL context
#if SOME_ENGINE_RENDER_API_OPENGL
        m_Context = CreateRef<OpenGLContext>();
#elif SOME_ENGINE_RENDER_API_OPENGLES
        m_Context = CreateRef<OpenGLESContext>();
#endif

        // 2. Init OpenGL context
        m_Context->Init(initInfo.WindowSys);
    }

    void OpenGLRenderSystemBase::Update(float deltaTime)
    {
        // TODO: Write your own game engine renderer main loop here:
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRenderSystemBase::Shutdown()
    {
        // Shutdown OpenGL Context
        m_Context->Shutdown();
        m_Context.reset();
    }

    void OpenGLRenderSystemBase::Present() { m_Context->SwapBuffers(); }

    void OpenGLRenderSystemBase::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        glViewport(x, y, width, height);
    }
} // namespace SomeEngineRuntime