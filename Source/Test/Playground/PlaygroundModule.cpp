/**
 * @file PlaygroundModule.cpp
 * @author Kexuan Zhang (zzxzzk115@gmail.com)
 * @brief 
 * @version 0.1.0
 * @date 2023-11-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "PlaygroundModule.h"
#include "SomeEngineRuntime/Core/Macro.h"
#include "SomeEngineRuntime/Function/GUI/GUI.h"

void PlaygroundModule::OnInit()
{
    SOME_ENGINE_INFO("[Playground] OnInit");
}

void PlaygroundModule::OnGUI()
{
#if SOME_ENGINE_GUI_IMPL_IMGUI
    ImGui::ShowDemoWindow();

    ImGui::Begin("SomeEngineDebugWindow");
    ImGui::Text("Hello, SomeEngine!");
    ImGui::End();
#endif
}

void PlaygroundModule::OnUpdate(float deltaTime)
{
    // SOME_ENGINE_INFO("[Playground] OnUpdate, deltaTime = {0} second", deltaTime);
}

void PlaygroundModule::OnDestroy()
{
    SOME_ENGINE_INFO("[Playground] OnDestroy");
}