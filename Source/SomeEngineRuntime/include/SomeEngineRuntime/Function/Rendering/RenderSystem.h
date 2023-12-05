/**
 * @file RenderSystem.h
 * @author Kexuan Zhang (zzxzzk115@gmail.com)
 * @brief
 * @version 0.1.0
 * @date 2023-11-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include "SomeEngineRuntime/Core/Base.h"

namespace SomeEngineRuntime
{
    class WindowSystem;

    struct RenderSystemInitInfo
    {
        Ref<WindowSystem> WindowSys;
    };

    class RenderSystem
    {
    public:
        virtual void Init(const RenderSystemInitInfo& initInfo)                           = 0;
        virtual void Update(float deltaTime)                                              = 0;
        virtual void Shutdown()                                                           = 0;
        virtual void Present()                                                            = 0;
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
    };
} // namespace SomeEngineRuntime
