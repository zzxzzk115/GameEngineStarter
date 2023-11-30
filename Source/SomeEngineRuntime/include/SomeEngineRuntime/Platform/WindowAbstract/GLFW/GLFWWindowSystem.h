/**
 * @file GLFWWindowSystem.h
 * @author Kexuan Zhang (zzxzzk115@gmail.com)
 * @brief
 * @version 0.1.0
 * @date 2023-11-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include "SomeEngineRuntime/Core/WindowSystem.h"

#include <GLFW/glfw3.h>
#if  SOME_ENGINE_PLATFORM_LINUX
#define GLFW_EXPOSE_NATIVE_X11
#elif SOME_ENGINE_PLATFORM_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#elif SOME_ENGINE_PLATFORM_DARWIN
#define GLFW_EXPOSE_NATIVE_COCOA
#endif
#include <GLFW/glfw3native.h>

namespace SomeEngineRuntime
{
    class GLFWWindowSystem : public WindowSystem
    {
    public:
        virtual void Init(const WindowSystemInitInfo& initInfo) override;

        virtual void Shutdown() override;

        bool OnUpdate() override;

        unsigned int GetWidth() const override { return m_Data.Width; }

        unsigned int GetHeight() const override { return m_Data.Height; }

        // Window attributes
        void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }

        virtual void* GetWindow() const override
        {
            return m_Window;
        }

        virtual void* GetNativeWindow() const override
        {
#if SOME_ENGINE_PLATFORM_LINUX
            return (void*)(uintptr_t)glfwGetX11Window(m_Window);
#elif SOME_ENGINE_PLATFORM_WINDOWS
            return glfwGetWin32Window(m_Window);
#elif SOME_ENGINE_PLATFORM_DARWIN
            return glfwGetCocoaWindow(m_Window);
#endif
        }

    private:
        GLFWwindow* m_Window;

        struct WindowData
        {
            std::string  Title;
            unsigned int Width, Height;

            EventCallbackFn EventCallback;
        };

        WindowData m_Data;
    };
} // namespace SomeEngineRuntime