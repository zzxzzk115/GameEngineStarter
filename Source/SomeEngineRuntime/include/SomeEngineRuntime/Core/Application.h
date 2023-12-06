/**
 * @file Application.h
 * @author Kexuan Zhang (zzxzzk115@gmail.com)
 * @brief
 * @version 0.1.0
 * @date 2023-11-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include "SomeEngineRuntime/Core/CustomModule/CustomModuleManager.h"
#include "SomeEngineRuntime/Core/Event/ApplicationEvent.h"
#include "SomeEngineRuntime/Platform/Platform.h"

#include <chrono>
#include <cstdint>
#include <string>

#if SOME_ENGINE_PLATFORM_ANDROID
struct android_app;
#endif

namespace SomeEngineRuntime
{
    struct ApplicationArgs
    {
        std::string Name         = "SomeEngine Application";
        uint32_t    WindowWidth  = 1024;
        uint32_t    WindowHeight = 768;
        void*       NativeApp    = nullptr;
    };

    class Application
    {
    public:
        Application(const ApplicationArgs& args);
        virtual ~Application();

        virtual void Run();
        virtual void Quit();

        virtual void OnEvent(Event& e);

        virtual void AddCustomModule(Ref<CustomModule> module);

        protected:
        virtual bool OnWindowClose(WindowCloseEvent& e);
        virtual bool OnWindowResize(WindowResizeEvent& e);

    protected:
        ApplicationArgs                                m_InitArgs;
        bool                                           m_IsMinimized   = false;
        bool                                           m_IsRunning     = true;
        std::chrono::high_resolution_clock::time_point m_LastFrameTime = std::chrono::high_resolution_clock::now();
        CustomModuleManager                            m_CustomModuleManager;

#if SOME_ENGINE_PLATFORM_ANDROID
        android_app* m_AndroidApp = nullptr;
#endif
    };
} // namespace SomeEngineRuntime