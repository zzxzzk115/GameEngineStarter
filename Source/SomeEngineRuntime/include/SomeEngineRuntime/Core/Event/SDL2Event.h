/**
 * @file SDL2Event.h
 * @author Kexuan Zhang (zzxzzk115@gmail.com)
 * @brief To handle SDL2 events
 * @version 0.1.0
 * @date 2023-12-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include "SomeEngineRuntime/Platform/Platform.h"

#if SOME_ENGINE_WINDOW_ABSTRACT_SDL
#include "SomeEngineRuntime/Core/Event/Event.h"

#include <SDL.h>

namespace SomeEngineRuntime
{
    class SDL2Event : public Event
    {
    public:
        SDL2Event(SDL_Event* event) : m_Event(event) {}

        SDL_Event* Get() const { return m_Event; }

        std::string ToString() const override
        {
            return "SDL2Event";
        }

        EVENT_CLASS_TYPE(SDL2)

        EVENT_CLASS_CATEGORY(EventCategoryPlatform)

    private:
        SDL_Event* m_Event;
    };
} // namespace SomeEngineRuntime

#endif