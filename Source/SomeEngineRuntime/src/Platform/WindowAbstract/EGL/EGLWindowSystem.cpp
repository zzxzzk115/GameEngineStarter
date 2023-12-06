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
#include "SomeEngineRuntime/Core/Event/MouseEvent.h"
#include "SomeEngineRuntime/Platform/Android/AndroidOut.h"

namespace SomeEngineRuntime
{
    void EGLWindowSystem::Init(const WindowSystemInitInfo& initInfo)
    {
        m_Data.Title  = initInfo.Title;
        m_Data.Width  = -1; // set to -1 because we have to query
        m_Data.Height = -1; // set to -1 because we have to query
        m_NativeApp   = static_cast<struct android_app*>(initInfo.NativeApp);
        m_Window      = static_cast<EGLNativeWindowType>(m_NativeApp->window);

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

        // handle input
        HandleInput();

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

    void EGLWindowSystem::HandleInput()
    {
        // handle all queued inputs
        auto* inputBuffer = android_app_swap_input_buffers(m_NativeApp);
        if (!inputBuffer)
        {
            // no inputs yet.
            return;
        }

        // handle motion events (motionEventsCounts can be 0).
        for (auto i = 0; i < inputBuffer->motionEventsCount; i++)
        {
            auto& motionEvent = inputBuffer->motionEvents[i];
            HandleMotionEvent(motionEvent);
        }
        // clear the motion input count in this render_buffer for main thread to re-use.
        android_app_clear_motion_events(inputBuffer);

        // handle input key events.
        for (auto i = 0; i < inputBuffer->keyEventsCount; i++)
        {
            auto& keyEvent = inputBuffer->keyEvents[i];
            aout << "Key: " << keyEvent.keyCode << " ";
            switch (keyEvent.action)
            {
                case AKEY_EVENT_ACTION_DOWN:
                    aout << "Key Down";
                    break;
                case AKEY_EVENT_ACTION_UP:
                    aout << "Key Up";
                    break;
                case AKEY_EVENT_ACTION_MULTIPLE:
                    // Deprecated since Android API level 29.
                    aout << "Multiple Key Actions";
                    break;
                default:
                    aout << "Unknown KeyEvent Action: " << keyEvent.action;
            }
            aout << std::endl;
        }
        // clear the key input count too.
        android_app_clear_key_events(inputBuffer);
    }

    void EGLWindowSystem::HandleMotionEvent(GameActivityMotionEvent& motionEvent)
    {
        auto action = motionEvent.action;

        // Find the pointer index, mask and bitshift to turn it into a readable value.
        auto pointerIndex =
            (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;

        // get the x and y position of this event if it is not ACTION_MOVE.
        auto& pointer = motionEvent.pointers[pointerIndex];
        auto  x       = GameActivityPointerAxes_getX(&pointer);
        auto  y       = GameActivityPointerAxes_getY(&pointer);

        MouseMovedEvent mouseMovedEvent(x, y);
        MouseButtonPressedEvent mouseButtonPressedEvent(0);
        MouseButtonReleasedEvent mouseButtonReleasedEvent(0);

        // determine the action type and process the event accordingly.
        switch (action & AMOTION_EVENT_ACTION_MASK)
        {
            case AMOTION_EVENT_ACTION_DOWN:
            case AMOTION_EVENT_ACTION_POINTER_DOWN:
                m_Data.EventCallback(mouseMovedEvent);
                m_Data.EventCallback(mouseButtonPressedEvent);
                break;

            case AMOTION_EVENT_ACTION_CANCEL:
                // treat the CANCEL as an UP event: doing nothing in the app, except
                // removing the pointer from the cache if pointers are locally saved.
                // code pass through on purpose.
            case AMOTION_EVENT_ACTION_UP:
            case AMOTION_EVENT_ACTION_POINTER_UP:
                m_Data.EventCallback(mouseMovedEvent);
                m_Data.EventCallback(mouseButtonReleasedEvent);
                break;

            case AMOTION_EVENT_ACTION_MOVE:
                // There is no pointer index for ACTION_MOVE, only a snapshot of
                // all active pointers; app needs to cache previous active pointers
                // to figure out which ones are actually moved.
                for (auto index = 0; index < motionEvent.pointerCount; index++)
                {
                    pointer = motionEvent.pointers[index];
                    x       = GameActivityPointerAxes_getX(&pointer);
                    y       = GameActivityPointerAxes_getY(&pointer);
                    m_Data.EventCallback(mouseMovedEvent);
                }
                break;
            default:
                break;
        }
    }
} // namespace SomeEngineRuntime
