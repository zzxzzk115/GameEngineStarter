/**
 * @file WindowSystem.h
 * @author Kexuan Zhang (zzxzzk115@gmail.com)
 * @brief
 * @version 0.1.0
 * @date 2023-11-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include "SomeEngineRuntime/Core/Event/Event.h"

#include <cstdint>
#include <functional>
#include <string>

namespace SomeEngineRuntime
{
    struct WindowSystemInitInfo
    {
        std::string Title;
        uint32_t    Width;
        uint32_t    Height;
        bool        VSync;

        WindowSystemInitInfo(const std::string& title  = "SomeEngine",
                       uint32_t           width  = 1024,
                       uint32_t           height = 768,
                       bool               vsync  = true) :
            Title(title),
            Width(width), Height(height), VSync(vsync)
        {}
    };

    // Interface representing a desktop system based WindowSystem
    class WindowSystem
    {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        WindowSystem()          = default;
        virtual ~WindowSystem() = default;

        virtual void Init(const WindowSystemInitInfo& props) = 0;

        virtual void Shutdown() = 0;

        virtual bool OnUpdate() = 0;

        virtual uint32_t GetWidth() const = 0;

        virtual uint32_t GetHeight() const = 0;

        virtual void MakeCurrentContext() = 0;
        virtual void SwapBuffers() = 0;

        // Window attributes
        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

        virtual void* GetWindow() const = 0;

        virtual void* GetNativeWindow() const = 0;
    };
} // namespace SomeEngineRuntime