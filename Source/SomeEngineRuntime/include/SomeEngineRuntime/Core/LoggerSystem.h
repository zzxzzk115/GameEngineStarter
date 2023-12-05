/**
 * @file LoggerSystem.h
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

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace SomeEngineRuntime
{
    class LoggerSystem
    {
    public:
        LoggerSystem();

        Ref<spdlog::logger>& GetCoreLogger() { return m_CoreLogger; }
        Ref<spdlog::logger>& GetClientLogger() { return m_ClientLogger; }

    private:
        Ref<spdlog::logger> m_CoreLogger;
        Ref<spdlog::logger> m_ClientLogger;
    };
} // namespace SomeEngineRuntime
