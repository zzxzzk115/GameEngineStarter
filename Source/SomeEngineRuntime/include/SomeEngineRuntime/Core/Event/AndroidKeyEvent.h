/**
 * @file AndroidKeyEvent.h
 * @author Kexuan Zhang (zzxzzk115@gmail.com)
 * @brief
 * @version 0.1.0
 * @date 2023-12-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "SomeEngineRuntime/Platform/Platform.h"

#if SOME_ENGINE_PLATFORM_ANDROID
#include "SomeEngineRuntime/Core/Event/Event.h"

#include <game-activity/GameActivity.h>

namespace SomeEngineRuntime
{
    class AndroidKeyEvent : public Event
    {
    public:
        AndroidKeyEvent(GameActivityKeyEvent* event) : m_Event(event) {}

        GameActivityKeyEvent* Get() const { return m_Event; }

        std::string ToString() const override { return "AndroidKeyEvent"; }

        EVENT_CLASS_TYPE(AndroidKey)

        EVENT_CLASS_CATEGORY(EventCategoryPlatform)

    private:
        GameActivityKeyEvent* m_Event;
    };
} // namespace SomeEngineRuntime
#endif
