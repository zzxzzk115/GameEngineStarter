/**
 * @file SDLWindowSystem.h
 * @author Kexuan Zhang (zzxzzk115@gmail.com)
 * @brief
 * @version 0.1.0
 * @date 2023-11-29
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include "SomeEngineRuntime/Core/WindowSystem.h"
#include "SomeEngineRuntime/Platform/Platform.h"

#include <SDL.h>

#if SOME_ENGINE_PLATFORM_WINDOWS
#include <SDL_syswm.h>
#endif

namespace SomeEngineRuntime
{
    using EventCallbackFn = std::function<void(Event&)>;

    struct WindowData
    {
        std::string  Title;
        unsigned int Width, Height;

        EventCallbackFn EventCallback;
    };

    class SDLWindowSystem : public WindowSystem
    {
    public:
        virtual void Init(const WindowSystemInitInfo& initInfo) override;

        virtual void Shutdown() override;

        bool OnUpdate() override;

        unsigned int GetWidth() const override { return m_Data.Width; }

        unsigned int GetHeight() const override { return m_Data.Height; }

        // Window attributes
        void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }

        virtual void* GetWindow() const override { return m_Window; }

        virtual void* GetNativeWindow() const override
        {
#if SOME_ENGINE_PLATFORM_DESKTOP
            SDL_SysWMinfo wmInfo;
            SDL_VERSION(&wmInfo.version);
            SDL_GetWindowWMInfo(m_Window, &wmInfo);
#if SOME_ENGINE_PLATFORM_WINDOWS
            return wmInfo.info.win.window;
#elif SOME_ENGINE_PLATFORM_LINUX
            return wmInfo.info.x11.window;
#elif SOME_ENGINE_PLATFORM_DARWIN
            return wmInfo.info.cocoa.window;
#else
            SOME_ENGINE_CORE_ERROR("[SDLWindowSystem] Unsupported Platform, failed to get the native window handle!");
            return nullptr;
#endif
#else
            SOME_ENGINE_CORE_ERROR("[SDLWindowSystem] Unsupported Platform, failed to get the native window handle!");
            return nullptr;
#endif
        }

    private:
        SDL_Window* m_Window;
        WindowData  m_Data;
    };
} // namespace SomeEngineRuntime
