/**
 * @file KeyCode.h
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
    using KeyCode = uint16_t;

    namespace Key
    {
#if SOME_ENGINE_WINDOW_ABSTRACT_GLFW
        // GLFW keycodes
        enum : KeyCode
        {
            Space      = 32,
            Apostrophe = 39, /* ' */
            Comma      = 44, /* , */
            Minus      = 45, /* - */
            Period     = 46, /* . */
            Slash      = 47, /* / */

            D0 = 48, /* 0 */
            D1 = 49, /* 1 */
            D2 = 50, /* 2 */
            D3 = 51, /* 3 */
            D4 = 52, /* 4 */
            D5 = 53, /* 5 */
            D6 = 54, /* 6 */
            D7 = 55, /* 7 */
            D8 = 56, /* 8 */
            D9 = 57, /* 9 */

            Semicolon = 59, /* ; */
            Equal     = 61, /* = */

            A = 65,
            B = 66,
            C = 67,
            D = 68,
            E = 69,
            F = 70,
            G = 71,
            H = 72,
            I = 73,
            J = 74,
            K = 75,
            L = 76,
            M = 77,
            N = 78,
            O = 79,
            P = 80,
            Q = 81,
            R = 82,
            S = 83,
            T = 84,
            U = 85,
            V = 86,
            W = 87,
            X = 88,
            Y = 89,
            Z = 90,

            LeftBracket  = 91, /* [ */
            Backslash    = 92, /* \ */
            RightBracket = 93, /* ] */
            GraveAccent  = 96, /* ` */

            World1 = 161, /* non-US #1 */
            World2 = 162, /* non-US #2 */

            /* Function keys */
            Escape      = 256,
            Enter       = 257,
            Tab         = 258,
            Backspace   = 259,
            Insert      = 260,
            Delete      = 261,
            Right       = 262,
            Left        = 263,
            Down        = 264,
            Up          = 265,
            PageUp      = 266,
            PageDown    = 267,
            Home        = 268,
            End         = 269,
            CapsLock    = 280,
            ScrollLock  = 281,
            NumLock     = 282,
            PrintScreen = 283,
            Pause       = 284,
            F1          = 290,
            F2          = 291,
            F3          = 292,
            F4          = 293,
            F5          = 294,
            F6          = 295,
            F7          = 296,
            F8          = 297,
            F9          = 298,
            F10         = 299,
            F11         = 300,
            F12         = 301,
            F13         = 302,
            F14         = 303,
            F15         = 304,
            F16         = 305,
            F17         = 306,
            F18         = 307,
            F19         = 308,
            F20         = 309,
            F21         = 310,
            F22         = 311,
            F23         = 312,
            F24         = 313,
            F25         = 314,

            /* Keypad */
            KP0        = 320,
            KP1        = 321,
            KP2        = 322,
            KP3        = 323,
            KP4        = 324,
            KP5        = 325,
            KP6        = 326,
            KP7        = 327,
            KP8        = 328,
            KP9        = 329,
            KPDecimal  = 330,
            KPDivide   = 331,
            KPMultiply = 332,
            KPSubtract = 333,
            KPAdd      = 334,
            KPEnter    = 335,
            KPEqual    = 336,

            LeftShift    = 340,
            LeftControl  = 341,
            LeftAlt      = 342,
            LeftSuper    = 343,
            RightShift   = 344,
            RightControl = 345,
            RightAlt     = 346,
            RightSuper   = 347,
            Menu         = 348
        };

#elif SOME_ENGINE_WINDOW_ABSTRACT_SDL
        // SDL2 keycodes
        enum : KeyCode
        {
            Space      = 32,
            Apostrophe = 39,
            Comma      = 44,
            Minus      = 45,
            Period     = 46,
            Slash      = 47,

            D0 = 48,
            D1 = 49,
            D2 = 50,
            D3 = 51,
            D4 = 52,
            D5 = 53,
            D6 = 54,
            D7 = 55,
            D8 = 56,
            D9 = 57,

            Semicolon = 59,
            Equal     = 61,

            A = 97,
            B = 98,
            C = 99,
            D = 100,
            E = 101,
            F = 102,
            G = 103,
            H = 104,
            I = 105,
            J = 106,
            K = 107,
            L = 108,
            M = 109,
            N = 110,
            O = 111,
            P = 112,
            Q = 113,
            R = 114,
            S = 115,
            T = 116,
            U = 117,
            V = 118,
            W = 119,
            X = 120,
            Y = 121,
            Z = 122,

            LeftBracket  = 91,
            Backslash    = 92,
            RightBracket = 93,
            GraveAccent  = 96,

            World1 = 161,
            World2 = 162,

            Escape      = 27,
            Enter       = 13,
            Tab         = 9,
            Backspace   = 8,
            Insert      = 277,
            Delete      = 127,
            Right       = 275,
            Left        = 276,
            Down        = 274,
            Up          = 273,
            PageUp      = 280,
            PageDown    = 281,
            Home        = 278,
            End         = 279,
            CapsLock    = 301,
            ScrollLock  = 302,
            NumLock     = 300,
            PrintScreen = 283,
            Pause       = 19,
            F1          = 282,
            F2          = 283,
            F3          = 284,
            F4          = 285,
            F5          = 286,
            F6          = 287,
            F7          = 288,
            F8          = 289,
            F9          = 290,
            F10         = 291,
            F11         = 292,
            F12         = 293,
            F13         = 294,
            F14         = 295,
            F15         = 296,
            F16         = 297,
            F17         = 298,
            F18         = 299,
            F19         = 300,
            F20         = 301,
            F21         = 302,
            F22         = 303,
            F23         = 304,
            F24         = 305,
            F25         = 306,

            KP0        = 256,
            KP1        = 257,
            KP2        = 258,
            KP3        = 259,
            KP4        = 260,
            KP5        = 261,
            KP6        = 262,
            KP7        = 263,
            KP8        = 264,
            KP9        = 265,
            KPDecimal  = 266,
            KPDivide   = 267,
            KPMultiply = 268,
            KPSubtract = 269,
            KPAdd      = 270,
            KPEnter    = 271,
            KPEqual    = 272,

            LeftShift    = 304,
            LeftControl  = 306,
            LeftAlt      = 308,
            LeftSuper    = 310,
            RightShift   = 305,
            RightControl = 307,
            RightAlt     = 309,
            RightSuper   = 311,
            Menu         = 319
        };
#endif
    } // namespace Key
} // namespace SomeEngineRuntime
