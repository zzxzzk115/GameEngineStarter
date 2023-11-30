/**
 * @file CustomModule.h
 * @author Kexuan Zhang (zzxzzk115@gmail.com)
 * @brief
 * @version 0.1.0
 * @date 2023-11-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include "SomeEngineRuntime/Core/Base.h"
#include "SomeEngineRuntime/Core/Event/Event.h"

namespace SomeEngineRuntime
{
    class CustomModule
    {
    public:
        CustomModule(const std::string& name = "CustomModule") : m_ModuleName(name) {}
        virtual ~CustomModule() = default;

        virtual void OnInit() {}

        virtual void OnGUI() {}

        virtual void OnUpdate(float deltaTime) {}

        virtual void OnDestroy() {}

        virtual void OnEvent(Event& event) {}

        inline const std::string& GetName() const { return m_ModuleName; }
    protected:
        std::string m_ModuleName;
    };
} // namespace SomeEngineRuntime
