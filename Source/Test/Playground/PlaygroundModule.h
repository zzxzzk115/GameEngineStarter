/**
 * @file PlaygroundModule.h
 * @author Kexuan Zhang (zzxzzk115@gmail.com)
 * @brief 
 * @version 0.1.0
 * @date 2023-11-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include "SomeEngineRuntime/Core/CustomModule/CustomModule.h"

class PlaygroundModule : public SomeEngineRuntime::CustomModule
{
public:
    PlaygroundModule() : SomeEngineRuntime::CustomModule("PlaygroundModule") {}
    virtual void OnInit() final;
    virtual void OnGUI() final;
    virtual void OnUpdate(float deltaTime) final;
    virtual void OnDestroy() final;
};