/**
 * @file ImGuiGUISystem.h
 * @author Kexuan Zhang (zzxzzk115@gmail.com)
 * @brief
 * @version 0.1.0
 * @date 2023-11-28
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include "SomeEngineRuntime/Function/GUI/GUISystem.h"

namespace SomeEngineRuntime
{
    class ImGuiGUISystem : public GUISystem
    {
    public:
        virtual void Init(const GUISystemInitInfo& initInfo) final;
        virtual void Shutdown() final;

        virtual void Update(float deltaTime) final;
        virtual void OnEvent(Event& e) final;

        virtual void Begin() final;
        virtual void End() final;

    private:
        bool m_IsBlockEvents = true;
    };
} // namespace SomeEngineRuntime
