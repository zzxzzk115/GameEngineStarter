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

#include <chrono>
#include <cstdint>
#include <string>

namespace SomeEngineRuntime
{
    struct ApplicationArgs
    {
        std::string Name         = "SomeEngine Application";
        uint32_t    WindowWidth  = 1024;
        uint32_t    WindowHeight = 768;
    };

    class Application
    {
    public:
        Application(const ApplicationArgs& args);
        ~Application();

        void Run();
        void Quit();

        void OnEvent(Event& e);

        void AddCustomModule(Ref<CustomModule> module);

    private:
        bool OnWindowClose(WindowCloseEvent& e);
        bool OnWindowResize(WindowResizeEvent& e);

    private:
        ApplicationArgs                                m_InitArgs;
        bool                                           m_IsMinimized   = false;
        bool                                           m_IsRunning     = true;
        std::chrono::high_resolution_clock::time_point m_LastFrameTime = std::chrono::high_resolution_clock::now();
        CustomModuleManager                            m_CustomModuleManager;
    };
} // namespace SomeEngineRuntime