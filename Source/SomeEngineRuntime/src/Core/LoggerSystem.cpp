/**
 * @file LoggerSystem.cpp
 * @author Kexuan Zhang (zzxzzk115@gmail.com)
 * @brief
 * @version 0.1.0
 * @date 2023-11-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "SomeEngineRuntime/Core/LoggerSystem.h"
#include "SomeEngineRuntime/Platform/Platform.h"

#if SOME_ENGINE_PLATFORM_ANDROID
#include "SomeEngineRuntime/Platform/Android/AndroidOut.h"
#include <spdlog/sinks/android_sink.h>
#else
#include <spdlog/sinks/basic_file_sink.h>
#endif

#include <spdlog/sinks/stdout_color_sinks.h>
#include <iostream>

namespace SomeEngineRuntime
{
    LoggerSystem::LoggerSystem()
    {
        std::vector<spdlog::sink_ptr> logSinks;

#if SOME_ENGINE_PLATFORM_ANDROID
        logSinks.emplace_back(std::make_shared<spdlog::sinks::android_sink_mt>("SomeEngine", "SomeEngine"));
        logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
#else
        logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("SomeEngine.log", true));
        logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
#endif

        logSinks[0]->set_pattern("%^[%T] %n: %v%$");
        logSinks[1]->set_pattern("[%T] [%l] %n: %v");

        m_CoreLogger = std::make_shared<spdlog::logger>("SOME_ENGINE_CORE", begin(logSinks), end(logSinks));
        spdlog::register_logger(m_CoreLogger);
        m_CoreLogger->set_level(spdlog::level::trace);
        m_CoreLogger->flush_on(spdlog::level::trace);

        m_ClientLogger = std::make_shared<spdlog::logger>("SOME_ENGINE_APP", begin(logSinks), end(logSinks));
        spdlog::register_logger(m_ClientLogger);
        m_ClientLogger->set_level(spdlog::level::trace);
        m_ClientLogger->flush_on(spdlog::level::trace);
    }
} // namespace SomeEngineRuntime
