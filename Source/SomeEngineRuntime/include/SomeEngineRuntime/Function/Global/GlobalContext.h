/**
 * @file GlobalContext.h
 * @author Kexuan Zhang (zzxzzk115@gmail.com)
 * @brief Provide a global context to access some Systems.
 * @version 0.1.0
 * @date 2023-11-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include "SomeEngineRuntime/Core/Base.h"
#include "SomeEngineRuntime/Platform/Platform.h"

#if SOME_ENGINE_PLATFORM_ANDROID
#include <game-activity/native_app_glue/android_native_app_glue.h>
#endif

#include <string>

namespace SomeEngineRuntime
{
    class LoggerSystem;
    class WindowSystem;
    class RenderSystem;
    class GUISystem;

    struct RuntimeGlobalContextInitInfo
    {
        std::string AppName;
        uint32_t    WindowWidth;
        uint32_t    WindowHeight;
        void*       NativeApp;
    };

    struct RuntimeGlobalContext
    {
        Ref<LoggerSystem> LoggerSys;
        Ref<WindowSystem> WindowSys;
        Ref<RenderSystem> RenderSys;
        Ref<GUISystem>    GUISys;
#if SOME_ENGINE_PLATFORM_ANDROID
        struct android_app* NativeApp;
#else
        void* NativeApp;
#endif

    public:
        void StartSystems(RuntimeGlobalContextInitInfo initInfo);
        void ShutdownSystems();
    };

    extern RuntimeGlobalContext g_RuntimeGlobalContext;
} // namespace SomeEngineRuntime
