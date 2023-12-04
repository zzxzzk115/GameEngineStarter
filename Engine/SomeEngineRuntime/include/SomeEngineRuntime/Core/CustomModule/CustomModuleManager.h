/**
 * @file CustomModuleManager.h
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
#include "SomeEngineRuntime/Core/CustomModule/CustomModule.h"

#include <vector>
#include <functional>

namespace SomeEngineRuntime
{
    class CustomModuleManager
    {
    public:
        CustomModuleManager() = default;

        void Shutdown();

        void AddModule(Ref<CustomModule> module);
        void RemoveModule(Ref<CustomModule> module);

        void Update(float deltaTime);

        void ForEach(std::function<void(Ref<CustomModule>)> callback);
        void ForEachIf(std::function<void(Ref<CustomModule>)> callback, std::function<bool(Ref<CustomModule>)> condition);

    private:
        std::vector<Ref<CustomModule>> m_Modules;
    };
} // namespace SomeEngineRuntime
