/**
 * @file EmscriptenStub.h
 * @author Kexuan Zhang (zzxzzk115@gmail.com)
 * @brief from https://github.com/ocornut/imgui/blob/master/examples/libs/emscripten/emscripten_mainloop_stub.h
 * @version 0.1
 * @date 2023-12-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "SomeEngineRuntime/Platform/Platform.h"

#if SOME_ENGINE_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#include <functional>
static std::function<void()>            MainLoopForEmscriptenP;
static void MainLoopForEmscripten()     { MainLoopForEmscriptenP(); }
#define EMSCRIPTEN_MAINLOOP_BEGIN       MainLoopForEmscriptenP = [&]()
#define EMSCRIPTEN_MAINLOOP_END         ; emscripten_set_main_loop(MainLoopForEmscripten, 0, true)
#else
#define EMSCRIPTEN_MAINLOOP_BEGIN
#define EMSCRIPTEN_MAINLOOP_END
#endif