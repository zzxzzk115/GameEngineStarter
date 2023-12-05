/**
 * @file main.cpp
 * @author Kexuan Zhang (zzxzzk115@gmail.com)
 * @brief
 * @version 0.1.0
 * @date 2023-11-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "PlaygroundApp.h"

int main()
{
#if !SOME_ENGINE_WINDOW_ABSTRACT_EGL // Not EGL then use Application
    SomeEngineRuntime::ApplicationArgs appArgs;
    appArgs.Name = "Playground";

    PlaygroundApp playgroundApp(appArgs);
    playgroundApp.Run();
#endif

    return 0;
}