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
    SomeEngineRuntime::ApplicationArgs appArgs;
    appArgs.Name = "Playground";

    PlaygroundApp playgroundApp(appArgs);
    playgroundApp.Run();

    return 0;
}