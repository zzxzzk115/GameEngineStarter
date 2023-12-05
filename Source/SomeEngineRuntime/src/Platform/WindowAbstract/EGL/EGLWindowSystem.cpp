/**
 * @file EGLWindowSystem.cpp
 * @author Kexuan Zhang (zzxzzk115@gmail.com)
 * @brief
 * @version 0.1.0
 * @date 2023-12-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "SomeEngineRuntime/Platform/WindowAbstract/EGL/EGLWindowSystem.h"
#include "SomeEngineRuntime/Core/Event/ApplicationEvent.h"

namespace SomeEngineRuntime
{
    void EGLWindowSystem::Init(const WindowSystemInitInfo& initInfo)
    {
        m_Data.Title  = initInfo.Title;
        m_Data.Width  = -1; // set to -1 because we have to query
        m_Data.Height = -1; // set to -1 because we have to query
        m_Window      = static_cast<EGLNativeWindowType>(initInfo.NativeWindow);

        SOME_ENGINE_CORE_INFO("[EGLWindowSystem] Creating window, name: {0}, resolution: {1} x {2}",
                              initInfo.Title,
                              initInfo.Width,
                              initInfo.Height);

        // render attributes
        constexpr EGLint attribs[] = {
            EGL_RENDERABLE_TYPE,
            EGL_OPENGL_ES3_BIT, // render type - opengl es 3
            EGL_SURFACE_TYPE,
            EGL_WINDOW_BIT, // surface type - use window
            EGL_BLUE_SIZE,
            8, // blue color render_buffer size - 8
            EGL_GREEN_SIZE,
            8, // green color render_buffer size - 8
            EGL_RED_SIZE,
            8, // red color render_buffer size - 8
            EGL_DEPTH_SIZE,
            24,      // depth size - 24
            EGL_NONE // end mark
        };

        // The default display is probably what you want on Android
        m_Display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        eglInitialize(m_Display, nullptr, nullptr);

        // figure out how many configs there are
        EGLint numConfigs;
        eglChooseConfig(m_Display, attribs, nullptr, 0, &numConfigs);

        // get the list of configurations
        std::unique_ptr<EGLConfig[]> supportedConfigs(new EGLConfig[numConfigs]);
        eglChooseConfig(m_Display, attribs, supportedConfigs.get(), numConfigs, &numConfigs);

        // Find a config we like.
        // Could likely just grab the first if we don't care about anything else in the config.
        // Otherwise hook in your own heuristic
        auto display = m_Display;
        m_Config     = *std::find_if(
            supportedConfigs.get(), supportedConfigs.get() + numConfigs, [&display](const EGLConfig& config) {
                EGLint red, green, blue, depth;
                if (eglGetConfigAttrib(display, config, EGL_RED_SIZE, &red) &&
                    eglGetConfigAttrib(display, config, EGL_GREEN_SIZE, &green) &&
                    eglGetConfigAttrib(display, config, EGL_BLUE_SIZE, &blue) &&
                    eglGetConfigAttrib(display, config, EGL_DEPTH_SIZE, &depth))
                {
                    // acout << "Found config with " << red << ", " << green << ", " << blue << ", " << depth <<
                    // std::endl;
                    return red == 8 && green == 8 && blue == 8 && depth == 24;
                }
                return false;
            });

        // create the proper window surface
        EGLint format;
        eglGetConfigAttrib(m_Display, m_Config, EGL_NATIVE_VISUAL_ID, &format);
        m_Surface = eglCreateWindowSurface(m_Display, m_Config, m_Window, nullptr);

        SOME_ENGINE_CORE_INFO("[EGLWindowSystem] Initialized");
    }

    void EGLWindowSystem::Shutdown()
    {
        if (m_Display != EGL_NO_DISPLAY)
        {
            eglMakeCurrent(m_Display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
            if (m_Context != EGL_NO_CONTEXT)
            {
                eglDestroyContext(m_Display, m_Context);
                m_Context = EGL_NO_CONTEXT;
            }
            if (m_Surface != EGL_NO_SURFACE)
            {
                eglDestroySurface(m_Display, m_Surface);
                m_Surface = EGL_NO_SURFACE;
            }
            eglTerminate(m_Display);
            m_Display = EGL_NO_DISPLAY;
        }
    }

    bool EGLWindowSystem::OnUpdate()
    {
        // query window size and set glViewport
        EGLint width;
        eglQuerySurface(m_Display, m_Surface, EGL_WIDTH, &width);

        EGLint height;
        eglQuerySurface(m_Display, m_Surface, EGL_HEIGHT, &height);

        if (width != m_Data.Width || height != m_Data.Height)
        {
            // Post event
            m_Data.Width  = width;
            m_Data.Height = height;

            WindowResizeEvent resizeEvent(m_Data.Width, m_Data.Height);
            m_Data.EventCallback(resizeEvent);
        }

        return true;
    }

    void EGLWindowSystem::MakeCurrentContext()
    {
        // Create a GLES 3 context
        const EGLint contextAttribs[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};
        m_Context                     = eglCreateContext(m_Display, m_Config, EGL_NO_CONTEXT, contextAttribs);

        eglMakeCurrent(m_Display, m_Surface, m_Surface, m_Context);
    }

    void EGLWindowSystem::SwapBuffers()
    {
        // Present the rendered image. This is an implicit glFlush.
        auto swapResult = eglSwapBuffers(m_Display, m_Surface);
        SOME_ENGINE_CORE_ASSERT(swapResult == EGL_TRUE, "[EGLWindowSystem] Failed to swapBuffers");
    }
} // namespace SomeEngineRuntime
