/**
 * @file MouseCode.h
 * @author Kexuan Zhang (zzxzzk115@gmail.com)
 * @brief
 * @version 0.1.0
 * @date 2023-11-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <cstdint>

namespace SomeEngineRuntime
{
    using MouseCode = uint16_t;

    namespace Mouse
    {
        #if SOME_ENGINE_WINDOW_ABSTRACT_GLFW
        // GLFW mouse button codes
        enum : MouseCode
        {
            Button_0 = 0,
            Button_1 = 1,
            Button_2 = 2,
            Button_3 = 3,
            Button_4 = 4,
            Button_5 = 5,
            Button_6 = 6,
            Button_7 = 7,

            ButtonLast   = Button_7,
            ButtonLeft   = Button_0,
            ButtonRight  = Button_1,
            ButtonMiddle = Button_2
        };

        #elif SOME_ENGINE_WINDOW_ABSTRACT_SDL
        // SDL2 mouse button codes
        enum : MouseCode
        {
            Button_0 = 1,
            Button_1 = 2,
            Button_2 = 3,
            Button_3 = 4,
            Button_4 = 5,
            Button_5 = 6,
            Button_6 = 7,
            Button_7 = 8,

            ButtonLast   = Button_7,
            ButtonLeft   = Button_1,
            ButtonRight  = Button_3,
            ButtonMiddle = Button_2
        };
        #endif
    }
} // namespace SomeEngineRuntime
