/**
 * @file GUISystem.h
 * @author Kexuan Zhang (zzxzzk115@gmail.com)
 * @brief
 * @version 0.1.0
 * @date 2023-11-28
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include "SomeEngineRuntime/Core/Base.h"
#include "SomeEngineRuntime/Core/Event/Event.h"

namespace SomeEngineRuntime
{
    class WindowSystem;

    struct GUISystemInitInfo
    {
        Ref<WindowSystem> WindowSys;
    };

    class GUISystem
    {
    public:
        virtual void Init(const GUISystemInitInfo& initInfo) = 0;
        virtual void Shutdown()                              = 0;

        virtual void Update(float deltaTime) = 0;
        virtual void OnEvent(Event& e)       = 0;

        virtual void Begin() = 0;
        virtual void End()   = 0;

    protected:
        Ref<WindowSystem> m_WindowSys;
    };
} // namespace SomeEngineRuntime