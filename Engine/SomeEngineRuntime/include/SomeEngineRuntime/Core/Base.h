/**
 * @file Base.h
 * @author Kexuan Zhang (zzxzzk115@gmail.com)
 * @brief
 * @version 0.1.0
 * @date 2023-11-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <memory>
#include <string>

namespace SomeEngineRuntime
{
    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T, typename... Args>
    constexpr Scope<T> CreateScope(Args&&... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T, typename... Args>
    constexpr Ref<T> CreateRef(Args&&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template<class... T>
    static std::string format(const char* fmt, const T&... t)
    {
        const auto  len = snprintf(nullptr, 0, fmt, t...);
        std::string r;
        r.resize(static_cast<size_t>(len) + 1);
        snprintf(&r.front(), len + 1, fmt, t...);
        r.resize(static_cast<size_t>(len));

        return r;
    }
} // namespace SomeEngineRuntime
