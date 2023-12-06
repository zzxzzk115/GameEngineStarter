/**
 * @file EGLWindowSystem.h
 * @author Kexuan Zhang (zzxzzk115@gmail.com)
 * @brief
 * @version 0.1.0
 * @date 2023-12-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include "SomeEngineRuntime/Core/WindowSystem.h"

#include <EGL/egl.h>

#include <game-activity/GameActivity.h>
#include <game-activity/native_app_glue/android_native_app_glue.h>

namespace SomeEngineRuntime
{
    class EGLWindowSystem : public WindowSystem
    {
    public:
        virtual void Init(const WindowSystemInitInfo& initInfo) override;

        virtual void Shutdown() override;

        virtual bool OnUpdate() override;

        virtual unsigned int GetWidth() const override { return m_Data.Width; }

        virtual unsigned int GetHeight() const override { return m_Data.Height; }

        virtual void MakeCurrentContext() override;
        virtual void SwapBuffers() override;

        // Window attributes
        virtual void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }

        // for others, Window is display.
        virtual void* GetWindow() const override { return m_Display; }

        // and NativeWindow is EGLNativeWindowType
        virtual void* GetNativeWindow() const override { return m_Window; }

    private:
        void HandleInput();
        void HandleMotionEvent(GameActivityMotionEvent& motionEvent);

    private:
        struct WindowData
        {
            std::string  Title;
            int Width, Height;

            EventCallbackFn EventCallback;
        };

        EGLNativeWindowType m_Window = nullptr;
        EGLConfig           m_Config;
        EGLDisplay          m_Display = EGL_NO_DISPLAY;
        EGLSurface          m_Surface = EGL_NO_SURFACE;
        EGLContext          m_Context = EGL_NO_CONTEXT;

        struct android_app* m_NativeApp = nullptr;

        WindowData m_Data;
    };
} // namespace SomeEngineRuntime
