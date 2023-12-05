/**
 * @file SDLWindowSystem.cpp
 * @author Kexuan Zhang (zzxzzk115@gmail.com)
 * @brief
 * @version 0.1.0
 * @date 2023-11-29
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "SomeEngineRuntime/Platform/WindowAbstract/SDL/SDLWindowSystem.h"

#include "SomeEngineRuntime/Core/Event/ApplicationEvent.h"
#include "SomeEngineRuntime/Core/Event/KeyEvent.h"
#include "SomeEngineRuntime/Core/Event/MouseEvent.h"
#include "SomeEngineRuntime/Core/Event/SDL2Event.h"

namespace SomeEngineRuntime
{
    void SDLWindowSystem::Init(const WindowSystemInitInfo& initInfo)
    {
        m_Data.Title  = initInfo.Title;
        m_Data.Width  = initInfo.Width;
        m_Data.Height = initInfo.Height;

        SOME_ENGINE_CORE_INFO("[SDLWindowSystem] Creating window, name: {0}, resolution: {1} x {2}",
                              initInfo.Title,
                              initInfo.Width,
                              initInfo.Height);

        // 1. Init SDL
        int sdlInit = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);
        SOME_ENGINE_CORE_ASSERT(!sdlInit, "[SDLWindowSystem] Failed to init SDL!");

        // 2. Setup GL versions
#if SOME_ENGINE_RENDER_API_OPENGL
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, SOME_ENGINE_RENDER_API_OPENGL_MIN_MAJOR);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, SOME_ENGINE_RENDER_API_OPENGL_MIN_MINOR);
#elif SOME_ENGINE_RENDER_API_OPENGLES
        // SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
        // Hard code 2.0 because 2.0+ sometimes fails.
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif
#if SOME_ENGINE_PLATFORM_DARWIN
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
#endif

        // From 2.0.18: Enable native IME.
#ifdef SDL_HINT_IME_SHOW_UI
        SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif

        // 3. Create window with graphics context
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
        SDL_WindowFlags windowFlags =
            (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
        m_Window = SDL_CreateWindow(m_Data.Title.c_str(),
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    (int)initInfo.Width,
                                    (int)initInfo.Height,
                                    windowFlags);

        SOME_ENGINE_CORE_INFO("[SDLWindowSystem] Initialized");
    }

    void SDLWindowSystem::Shutdown()
    {
        SDL_DestroyWindow(m_Window);
        SDL_Quit();
    }

    bool SDLWindowSystem::OnUpdate()
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            // Dispatch SDL2 events for other systems (e.g. imgui)
            SDL2Event sdl2Event(&e);
            m_Data.EventCallback(sdl2Event);

            switch (e.type)
            {
                case SDL_WINDOWEVENT:
                    if (e.window.event == SDL_WINDOWEVENT_RESIZED)
                    {
                        m_Data.Width  = e.window.data1;
                        m_Data.Height = e.window.data2;

                        WindowResizeEvent resizeEvent(m_Data.Width, m_Data.Height);
                        m_Data.EventCallback(resizeEvent);
                    }
                    break;

                case SDL_QUIT: {
                    return false;
                }
                break;

                case SDL_KEYDOWN: {
                    KeyPressedEvent keyEvent(e.key.keysym.scancode, 0);
                    m_Data.EventCallback(keyEvent);
                }
                break;

                case SDL_KEYUP: {
                    KeyReleasedEvent keyEvent(e.key.keysym.scancode);
                    m_Data.EventCallback(keyEvent);
                }
                break;

                case SDL_TEXTINPUT: {
                    KeyTypedEvent typedEvent(e.text.text[0]);
                    m_Data.EventCallback(typedEvent);
                }
                break;

                case SDL_MOUSEBUTTONDOWN: {
                    MouseButtonPressedEvent mouseEvent(e.button.button);
                    m_Data.EventCallback(mouseEvent);
                }
                break;

                case SDL_MOUSEBUTTONUP: {
                    MouseButtonReleasedEvent mouseEvent(e.button.button);
                    m_Data.EventCallback(mouseEvent);
                }
                break;

                case SDL_MOUSEMOTION: {
                    MouseMovedEvent mouseEvent(e.motion.x, e.motion.y);
                    m_Data.EventCallback(mouseEvent);
                }
                break;

                case SDL_MOUSEWHEEL: {
                    MouseScrolledEvent scrollEvent(e.wheel.x, e.wheel.y);
                    m_Data.EventCallback(scrollEvent);
                }
                break;
            }
        }

        return true;
    }

    void SDLWindowSystem::MakeCurrentContext()
    {
        SDL_GLContext glContext = SDL_GL_CreateContext(m_Window);
        SOME_ENGINE_CORE_ASSERT(!glContext, "[SDLWindowSystem] Failed to create SDL GL Context!");
        SDL_GL_MakeCurrent(m_Window, glContext);
    }

    void SDLWindowSystem::SwapBuffers() { SDL_GL_SwapWindow(m_Window); }
} // namespace SomeEngineRuntime
