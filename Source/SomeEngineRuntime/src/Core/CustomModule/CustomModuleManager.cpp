/**
 * @file CustomModuleManager.cpp
 * @author Kexuan Zhang (zzxzzk115@gmail.com)
 * @brief
 * @version 0.1.0
 * @date 2023-11-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "SomeEngineRuntime/Core/CustomModule/CustomModuleManager.h"

#include <algorithm>

namespace SomeEngineRuntime
{
    void CustomModuleManager::Shutdown()
    {
        ForEach([](Ref<CustomModule> module) { module->OnDestroy(); });
    }

    void CustomModuleManager::AddModule(Ref<CustomModule> module) { m_Modules.emplace_back(module); }

    void CustomModuleManager::RemoveModule(Ref<CustomModule> module)
    {
        auto it = std::find(m_Modules.begin(), m_Modules.end(), module);
        if (it != m_Modules.end())
        {
            module->OnDestroy();
            m_Modules.erase(it);
        }
    }

    void CustomModuleManager::Update(float deltaTime)
    {
        ForEach([deltaTime](Ref<CustomModule> module) { module->OnUpdate(deltaTime); });
    }

    void CustomModuleManager::ForEach(std::function<void(Ref<CustomModule>)> callback)
    {
        for (const auto& module : m_Modules)
        {
            callback(module);
        }
    }

    void CustomModuleManager::ForEachIf(std::function<void(Ref<CustomModule>)> callback,
                                        std::function<bool(Ref<CustomModule>)> condition)
    {
        for (const auto& module : m_Modules)
        {
            if (!condition(module))
                break;
            callback(module);
        }
    }
} // namespace SomeEngineRuntime
