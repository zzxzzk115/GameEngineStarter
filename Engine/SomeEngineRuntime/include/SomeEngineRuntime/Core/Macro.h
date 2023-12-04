/**
 * @file Macro.h
 * @author Kexuan Zhang (zzxzzk115@gmail.com)
 * @brief
 * @version 0.1.0
 * @date 2023-11-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include "SomeEngineRuntime/Core/LoggerSystem.h"
#include "SomeEngineRuntime/Function/Global/GlobalContext.h"
#include "SomeEngineRuntime/Platform/Platform.h"

#ifndef NDEBUG
#if SOME_ENGINE_PLATFORM_WINDOWS
#define SOME_ENGINE_DEBUGBREAK() __debugbreak()
#elif SOME_ENGINE_PLATFORM_LINUX || SOME_ENGINE_PLATFORM_DARWIN
#include <signal.h>
#define SOME_ENGINE_DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak yet!"
#endif
#define SOME_ENGINE_ENABLE_ASSERTS
#else
#define SOME_ENGINE_DEBUGBREAK()
#endif

#define SOME_ENGINE_EXPAND_MACRO(x) x
#define SOME_ENGINE_STRINGIFY_MACRO(x) #x

#define SOME_ENGINE_ARRAYSIZE(_ARR) \
    ((int)(sizeof(_ARR) / sizeof(*(_ARR)))) // Size of a static C-style array. Don't use on pointers!

// Core log macros
#define SOME_ENGINE_CORE_TRACE(...) ::SomeEngineRuntime::g_RuntimeGlobalContext.LoggerSys->GetCoreLogger()->trace(__VA_ARGS__)
#define SOME_ENGINE_CORE_INFO(...) ::SomeEngineRuntime::g_RuntimeGlobalContext.LoggerSys->GetCoreLogger()->info(__VA_ARGS__)
#define SOME_ENGINE_CORE_WARN(...) ::SomeEngineRuntime::g_RuntimeGlobalContext.LoggerSys->GetCoreLogger()->warn(__VA_ARGS__)
#define SOME_ENGINE_CORE_ERROR(...) ::SomeEngineRuntime::g_RuntimeGlobalContext.LoggerSys->GetCoreLogger()->error(__VA_ARGS__)
#define SOME_ENGINE_CORE_CRITICAL(...) \
    ::SomeEngineRuntime::g_RuntimeGlobalContext.LoggerSys->GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define SOME_ENGINE_TRACE(...) ::SomeEngineRuntime::g_RuntimeGlobalContext.LoggerSys->GetClientLogger()->trace(__VA_ARGS__)
#define SOME_ENGINE_INFO(...) ::SomeEngineRuntime::g_RuntimeGlobalContext.LoggerSys->GetClientLogger()->info(__VA_ARGS__)
#define SOME_ENGINE_WARN(...) ::SomeEngineRuntime::g_RuntimeGlobalContext.LoggerSys->GetClientLogger()->warn(__VA_ARGS__)
#define SOME_ENGINE_ERROR(...) ::SomeEngineRuntime::g_RuntimeGlobalContext.LoggerSys->GetClientLogger()->error(__VA_ARGS__)
#define SOME_ENGINE_CRITICAL(...) ::SomeEngineRuntime::g_RuntimeGlobalContext.LoggerSys->GetClientLogger()->critical(__VA_ARGS__)

#define BIT(x) (1 << x)

#define SOME_ENGINE_BIND_EVENT_FN(fn) \
    [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

// Asserts
#ifdef SOME_ENGINE_ENABLE_ASSERTS

// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the
// default message
#define SOME_ENGINE_INTERNAL_ASSERT_IMPL(type, check, msg, ...) \
    { \
        if (!(check)) \
        { \
            SOME_ENGINE##type##ERROR(msg, __VA_ARGS__); \
            SOME_ENGINE_DEBUGBREAK(); \
        } \
    }
#define SOME_ENGINE_INTERNAL_ASSERT_WITH_MSG(type, check, ...) \
    SOME_ENGINE_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define SOME_ENGINE_INTERNAL_ASSERT_NO_MSG(type, check) \
    SOME_ENGINE_INTERNAL_ASSERT_IMPL(type, \
                             check, \
                             "Assertion '{0}' failed at {1}:{2}", \
                             SOME_ENGINE_STRINGIFY_MACRO(check), \
                             std::filesystem::path(__FILE__).filename().string(), \
                             __LINE__)

#define SOME_ENGINE_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define SOME_ENGINE_INTERNAL_ASSERT_GET_MACRO(...) \
    SOME_ENGINE_EXPAND_MACRO( \
        SOME_ENGINE_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, SOME_ENGINE_INTERNAL_ASSERT_WITH_MSG, SOME_ENGINE_INTERNAL_ASSERT_NO_MSG))

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define SOME_ENGINE_ASSERT(...) SOME_ENGINE_EXPAND_MACRO(SOME_ENGINE_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__))
#define SOME_ENGINE_CORE_ASSERT(...) SOME_ENGINE_EXPAND_MACRO(SOME_ENGINE_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__))
#else
#define SOME_ENGINE_ASSERT(...)
#define SOME_ENGINE_CORE_ASSERT(...)
#endif