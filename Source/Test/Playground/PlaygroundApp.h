/**
 * @file PlaygroundApp.h
 * @author Kexuan Zhang (zzxzzk115@gmail.com)
 * @brief 
 * @version 0.1.0
 * @date 2023-11-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include "PlaygroundModule.h"

#include <SomeEngineRuntime/Core/Application.h>
#include <SomeEngineRuntime/Core/Macro.h>

class PlaygroundApp : public SomeEngineRuntime::Application
{
public:
    PlaygroundApp(const SomeEngineRuntime::ApplicationArgs& args) : SomeEngineRuntime::Application(args)
    {
        SOME_ENGINE_INFO("Hello, {0}!", args.Name);
        AddCustomModule(SomeEngineRuntime::CreateRef<PlaygroundModule>());
    }

    ~PlaygroundApp() {}
};