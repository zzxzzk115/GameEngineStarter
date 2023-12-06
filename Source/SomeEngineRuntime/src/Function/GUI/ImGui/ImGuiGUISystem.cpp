/**
 * @file ImGuiGUISystem.cpp
 * @author Kexuan Zhang (zzxzzk115@gmail.com)
 * @brief
 * @version 0.1.0
 * @date 2023-11-28
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "SomeEngineRuntime/Function/GUI/ImGui/ImGuiGUISystem.h"
#include "SomeEngineRuntime/Function/Global/GlobalContext.h"
#include "SomeEngineRuntime/Platform/Platform.h"

#include <imgui.h>

#if SOME_ENGINE_RENDER_API_OPENGL || SOME_ENGINE_RENDER_API_OPENGLES
#include <imgui_impl_opengl3.h>
#endif

#if SOME_ENGINE_WINDOW_ABSTRACT_GLFW
#include "SomeEngineRuntime/Platform/WindowAbstract/GLFW/GLFWWindowSystem.h"
#include <imgui_impl_glfw.h>
#elif SOME_ENGINE_WINDOW_ABSTRACT_SDL
#include "SomeEngineRuntime/Core/Event/SDL2Event.h"
#include "SomeEngineRuntime/Platform/WindowAbstract/SDL/SDLWindowSystem.h"
#include <imgui_impl_sdl2.h>
#elif SOME_ENGINE_WINDOW_ABSTRACT_EGL
#include "SomeEngineRuntime/Core/Event/AndroidKeyEvent.h"
#include "SomeEngineRuntime/Core/Event/MouseEvent.h"
#include "SomeEngineRuntime/Platform/WindowAbstract/EGL/EGLWindowSystem.h"
#include <android/keycodes.h>
#include <game-activity/GameActivity.h>
#include <imgui_impl_android.h>

static ImGuiKey ImGui_ImplAndroid_KeyCodeToImGuiKey(int32_t key_code)
{
    switch (key_code)
    {
        case AKEYCODE_TAB:
            return ImGuiKey_Tab;
        case AKEYCODE_DPAD_LEFT:
            return ImGuiKey_LeftArrow;
        case AKEYCODE_DPAD_RIGHT:
            return ImGuiKey_RightArrow;
        case AKEYCODE_DPAD_UP:
            return ImGuiKey_UpArrow;
        case AKEYCODE_DPAD_DOWN:
            return ImGuiKey_DownArrow;
        case AKEYCODE_PAGE_UP:
            return ImGuiKey_PageUp;
        case AKEYCODE_PAGE_DOWN:
            return ImGuiKey_PageDown;
        case AKEYCODE_MOVE_HOME:
            return ImGuiKey_Home;
        case AKEYCODE_MOVE_END:
            return ImGuiKey_End;
        case AKEYCODE_INSERT:
            return ImGuiKey_Insert;
        case AKEYCODE_FORWARD_DEL:
            return ImGuiKey_Delete;
        case AKEYCODE_DEL:
            return ImGuiKey_Backspace;
        case AKEYCODE_SPACE:
            return ImGuiKey_Space;
        case AKEYCODE_ENTER:
            return ImGuiKey_Enter;
        case AKEYCODE_ESCAPE:
            return ImGuiKey_Escape;
        case AKEYCODE_APOSTROPHE:
            return ImGuiKey_Apostrophe;
        case AKEYCODE_COMMA:
            return ImGuiKey_Comma;
        case AKEYCODE_MINUS:
            return ImGuiKey_Minus;
        case AKEYCODE_PERIOD:
            return ImGuiKey_Period;
        case AKEYCODE_SLASH:
            return ImGuiKey_Slash;
        case AKEYCODE_SEMICOLON:
            return ImGuiKey_Semicolon;
        case AKEYCODE_EQUALS:
            return ImGuiKey_Equal;
        case AKEYCODE_LEFT_BRACKET:
            return ImGuiKey_LeftBracket;
        case AKEYCODE_BACKSLASH:
            return ImGuiKey_Backslash;
        case AKEYCODE_RIGHT_BRACKET:
            return ImGuiKey_RightBracket;
        case AKEYCODE_GRAVE:
            return ImGuiKey_GraveAccent;
        case AKEYCODE_CAPS_LOCK:
            return ImGuiKey_CapsLock;
        case AKEYCODE_SCROLL_LOCK:
            return ImGuiKey_ScrollLock;
        case AKEYCODE_NUM_LOCK:
            return ImGuiKey_NumLock;
        case AKEYCODE_SYSRQ:
            return ImGuiKey_PrintScreen;
        case AKEYCODE_BREAK:
            return ImGuiKey_Pause;
        case AKEYCODE_NUMPAD_0:
            return ImGuiKey_Keypad0;
        case AKEYCODE_NUMPAD_1:
            return ImGuiKey_Keypad1;
        case AKEYCODE_NUMPAD_2:
            return ImGuiKey_Keypad2;
        case AKEYCODE_NUMPAD_3:
            return ImGuiKey_Keypad3;
        case AKEYCODE_NUMPAD_4:
            return ImGuiKey_Keypad4;
        case AKEYCODE_NUMPAD_5:
            return ImGuiKey_Keypad5;
        case AKEYCODE_NUMPAD_6:
            return ImGuiKey_Keypad6;
        case AKEYCODE_NUMPAD_7:
            return ImGuiKey_Keypad7;
        case AKEYCODE_NUMPAD_8:
            return ImGuiKey_Keypad8;
        case AKEYCODE_NUMPAD_9:
            return ImGuiKey_Keypad9;
        case AKEYCODE_NUMPAD_DOT:
            return ImGuiKey_KeypadDecimal;
        case AKEYCODE_NUMPAD_DIVIDE:
            return ImGuiKey_KeypadDivide;
        case AKEYCODE_NUMPAD_MULTIPLY:
            return ImGuiKey_KeypadMultiply;
        case AKEYCODE_NUMPAD_SUBTRACT:
            return ImGuiKey_KeypadSubtract;
        case AKEYCODE_NUMPAD_ADD:
            return ImGuiKey_KeypadAdd;
        case AKEYCODE_NUMPAD_ENTER:
            return ImGuiKey_KeypadEnter;
        case AKEYCODE_NUMPAD_EQUALS:
            return ImGuiKey_KeypadEqual;
        case AKEYCODE_CTRL_LEFT:
            return ImGuiKey_LeftCtrl;
        case AKEYCODE_SHIFT_LEFT:
            return ImGuiKey_LeftShift;
        case AKEYCODE_ALT_LEFT:
            return ImGuiKey_LeftAlt;
        case AKEYCODE_META_LEFT:
            return ImGuiKey_LeftSuper;
        case AKEYCODE_CTRL_RIGHT:
            return ImGuiKey_RightCtrl;
        case AKEYCODE_SHIFT_RIGHT:
            return ImGuiKey_RightShift;
        case AKEYCODE_ALT_RIGHT:
            return ImGuiKey_RightAlt;
        case AKEYCODE_META_RIGHT:
            return ImGuiKey_RightSuper;
        case AKEYCODE_MENU:
            return ImGuiKey_Menu;
        case AKEYCODE_0:
            return ImGuiKey_0;
        case AKEYCODE_1:
            return ImGuiKey_1;
        case AKEYCODE_2:
            return ImGuiKey_2;
        case AKEYCODE_3:
            return ImGuiKey_3;
        case AKEYCODE_4:
            return ImGuiKey_4;
        case AKEYCODE_5:
            return ImGuiKey_5;
        case AKEYCODE_6:
            return ImGuiKey_6;
        case AKEYCODE_7:
            return ImGuiKey_7;
        case AKEYCODE_8:
            return ImGuiKey_8;
        case AKEYCODE_9:
            return ImGuiKey_9;
        case AKEYCODE_A:
            return ImGuiKey_A;
        case AKEYCODE_B:
            return ImGuiKey_B;
        case AKEYCODE_C:
            return ImGuiKey_C;
        case AKEYCODE_D:
            return ImGuiKey_D;
        case AKEYCODE_E:
            return ImGuiKey_E;
        case AKEYCODE_F:
            return ImGuiKey_F;
        case AKEYCODE_G:
            return ImGuiKey_G;
        case AKEYCODE_H:
            return ImGuiKey_H;
        case AKEYCODE_I:
            return ImGuiKey_I;
        case AKEYCODE_J:
            return ImGuiKey_J;
        case AKEYCODE_K:
            return ImGuiKey_K;
        case AKEYCODE_L:
            return ImGuiKey_L;
        case AKEYCODE_M:
            return ImGuiKey_M;
        case AKEYCODE_N:
            return ImGuiKey_N;
        case AKEYCODE_O:
            return ImGuiKey_O;
        case AKEYCODE_P:
            return ImGuiKey_P;
        case AKEYCODE_Q:
            return ImGuiKey_Q;
        case AKEYCODE_R:
            return ImGuiKey_R;
        case AKEYCODE_S:
            return ImGuiKey_S;
        case AKEYCODE_T:
            return ImGuiKey_T;
        case AKEYCODE_U:
            return ImGuiKey_U;
        case AKEYCODE_V:
            return ImGuiKey_V;
        case AKEYCODE_W:
            return ImGuiKey_W;
        case AKEYCODE_X:
            return ImGuiKey_X;
        case AKEYCODE_Y:
            return ImGuiKey_Y;
        case AKEYCODE_Z:
            return ImGuiKey_Z;
        case AKEYCODE_F1:
            return ImGuiKey_F1;
        case AKEYCODE_F2:
            return ImGuiKey_F2;
        case AKEYCODE_F3:
            return ImGuiKey_F3;
        case AKEYCODE_F4:
            return ImGuiKey_F4;
        case AKEYCODE_F5:
            return ImGuiKey_F5;
        case AKEYCODE_F6:
            return ImGuiKey_F6;
        case AKEYCODE_F7:
            return ImGuiKey_F7;
        case AKEYCODE_F8:
            return ImGuiKey_F8;
        case AKEYCODE_F9:
            return ImGuiKey_F9;
        case AKEYCODE_F10:
            return ImGuiKey_F10;
        case AKEYCODE_F11:
            return ImGuiKey_F11;
        case AKEYCODE_F12:
            return ImGuiKey_F12;
        default:
            return ImGuiKey_None;
    }
}

#endif

namespace SomeEngineRuntime
{
    void ImGuiGUISystem::Init(const GUISystemInitInfo& initInfo)
    {
        m_WindowSys = initInfo.WindowSys;

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport
        // io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
        // io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

        ImGui::StyleColorsDark();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular
        // ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding              = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
            style.PopupRounding = style.TabRounding = 6.0f;
        }

        // if on Android, set scale
#if SOME_ENGINE_WINDOW_ABSTRACT_EGL && SOME_ENGINE_PLATFORM_ANDROID
        // We load the default font with increased size to improve readability on many devices with "high" DPI.
        // FIXME: Put some effort into DPI awareness.
        // Important: when calling AddFontFromMemoryTTF(), ownership of font_data is transfered by Dear ImGui by default
        // (deleted is handled by Dear ImGui), unless we set FontDataOwnedByAtlas=false in ImFontConfig
        ImFontConfig font_cfg;
        font_cfg.SizePixels = 22.0f;
        io.Fonts->AddFontDefault(&font_cfg);

        // Arbitrary scale-up
        // FIXME: Put some effort into DPI awareness
        style.ScaleAllSizes(3.0f);
#endif

        // SetDarkThemeColors(); // you can set your own colors.

        // Setup Platform/Renderer bindings
#if SOME_ENGINE_WINDOW_ABSTRACT_GLFW
        ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)m_WindowSys->GetWindow(), true);
#elif SOME_ENGINE_WINDOW_ABSTRACT_SDL
        ImGui_ImplSDL2_InitForOpenGL((SDL_Window*)m_WindowSys->GetWindow(), SDL_GL_GetCurrentContext());
#elif SOME_ENGINE_WINDOW_ABSTRACT_EGL && SOME_ENGINE_PLATFORM_ANDROID
        ImGui_ImplAndroid_Init((ANativeWindow*)m_WindowSys->GetNativeWindow());
#endif

#if SOME_ENGINE_RENDER_API_OPENGL
        ImGui_ImplOpenGL3_Init("#version 330");
#elif SOME_ENGINE_RENDER_API_OPENGLES
        ImGui_ImplOpenGL3_Init("#version 100");
#endif

        SOME_ENGINE_CORE_INFO("[ImGuiGUISystem] Initialized");
    }

    void ImGuiGUISystem::Shutdown()
    {
#if SOME_ENGINE_RENDER_API_OPENGL || SOME_ENGINE_RENDER_API_OPENGLES
        ImGui_ImplOpenGL3_Shutdown();
#endif
#if SOME_ENGINE_WINDOW_ABSTRACT_GLFW
        ImGui_ImplGlfw_Shutdown();
#elif SOME_ENGINE_WINDOW_ABSTRACT_SDL
        ImGui_ImplSDL2_Shutdown();
#elif SOME_ENGINE_WINDOW_ABSTRACT_EGL && SOME_ENGINE_PLATFORM_ANDROID
        ImGui_ImplAndroid_Shutdown();
#endif
        ImGui::DestroyContext();
    }

    void ImGuiGUISystem::Update(float deltaTime)
    {
        // TODO: test only, remove
#if SOME_ENGINE_WINDOW_ABSTRACT_EGL && SOME_ENGINE_PLATFORM_ANDROID
        ImGuiIO& io = ImGui::GetIO();
        // Open on-screen (soft) input if requested by Dear ImGui
        static bool WantTextInputLast = false;
        if (io.WantTextInput && !WantTextInputLast)
            GameActivity_showSoftInput(g_RuntimeGlobalContext.NativeApp->activity,
                                       GAMEACTIVITY_SHOW_SOFT_INPUT_IMPLICIT);
        else if (!io.WantTextInput && WantTextInputLast)
        {
            GameActivity_hideSoftInput(g_RuntimeGlobalContext.NativeApp->activity,
                                       GAMEACTIVITY_HIDE_SOFT_INPUT_IMPLICIT_ONLY);
        }
        WantTextInputLast = io.WantTextInput;

        ImGui::ShowDemoWindow();

        ImGui::Begin("SomeEngineDebugWindow");
        ImGui::Text("Hello, SomeEngine!");
        ImGui::End();
#endif
    }

    void ImGuiGUISystem::OnEvent(Event& e)
    {
        // handle for SDL2 events
#if SOME_ENGINE_WINDOW_ABSTRACT_SDL
        if (e.GetEventType() == EventType::SDL2)
        {
            auto sdl2Event = static_cast<SDL2Event&>(e);
            ImGui_ImplSDL2_ProcessEvent(sdl2Event.Get());
            e.Handled = true;
            return;
        }
#elif SOME_ENGINE_WINDOW_ABSTRACT_EGL
        ImGuiIO& io = ImGui::GetIO();

        // AndroidKey, MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
        switch (e.GetEventType())
        {
                //     case EventType::KeyPressed: {
                //         auto     keyPressedEvent = static_cast<KeyPressedEvent&>(e);
                //         KeyCode  eventKeyCode    = keyPressedEvent.GetKeyCode();
                //         int32_t  eventScanCode   = keyPressedEvent.GetNativeScanCode();
                //         ImGuiKey key             = ImGui_ImplAndroid_KeyCodeToImGuiKey(eventKeyCode);
                //         SOME_ENGINE_CORE_INFO("[ImGuiGUISystem][OnEvent] KeyPressedEvent: {0}", key);
                //         io.AddKeyEvent(key, true);
                //         io.SetKeyEventNativeData(key, eventKeyCode, eventScanCode);
                //     }
                //     break;

                //     case EventType::KeyReleased: {
                //         auto     keyReleasedEvent = static_cast<KeyReleasedEvent&>(e);
                //         KeyCode  eventKeyCode     = keyReleasedEvent.GetKeyCode();
                //         int32_t  eventScanCode    = keyReleasedEvent.GetNativeScanCode();
                //         ImGuiKey key              = ImGui_ImplAndroid_KeyCodeToImGuiKey(eventKeyCode);
                //         SOME_ENGINE_CORE_INFO("[ImGuiGUISystem][OnEvent] KeyReleasedEvent: {0}", key);
                //         io.AddKeyEvent(key, false);
                //         io.SetKeyEventNativeData(key, eventKeyCode, eventScanCode);
                //     }
                //     break;

            case EventType::AndroidKey: {
                auto    androidKeyEvent = static_cast<AndroidKeyEvent&>(e);
                auto    keyEvent        = *androidKeyEvent.Get();
                int32_t keyCode         = keyEvent.keyCode;
                int32_t scanCode        = keyEvent.scanCode;
                int32_t action          = keyEvent.action;
                int32_t metaState       = keyEvent.metaState;

                io.AddKeyEvent(ImGuiMod_Ctrl, (metaState & AMETA_CTRL_ON) != 0);
                io.AddKeyEvent(ImGuiMod_Shift, (metaState & AMETA_SHIFT_ON) != 0);
                io.AddKeyEvent(ImGuiMod_Alt, (metaState & AMETA_ALT_ON) != 0);
                io.AddKeyEvent(ImGuiMod_Super, (metaState & AMETA_META_ON) != 0);

                switch (action)
                {
                    // FIXME: AKEY_EVENT_ACTION_DOWN and AKEY_EVENT_ACTION_UP occur at once as soon as a touch pointer
                    // goes up from a key. We use a simple key event queue/ and process one event per key per frame in
                    // ImGui_ImplAndroid_NewFrame()...or consider using IO queue, if suitable:
                    // https://github.com/ocornut/imgui/issues/2787
                    case AKEY_EVENT_ACTION_DOWN:
                    case AKEY_EVENT_ACTION_UP: {
                        ImGuiKey key = ImGui_ImplAndroid_KeyCodeToImGuiKey(keyCode);
                        if (key != ImGuiKey_None)
                        {
                            io.AddKeyEvent(key, action == AKEY_EVENT_ACTION_DOWN);

                            // hack for input text
                            if (action == AKEY_EVENT_ACTION_DOWN)
                            {
                                io.AddInputCharacter(keyEvent.unicodeChar);
                            }

                            io.SetKeyEventNativeData(key, keyCode, scanCode);
                        }

                        break;
                    }
                    default:
                        break;
                }
                e.Handled = true;
                break;
            }

            case EventType::MouseButtonPressed: {
                io.AddMouseButtonEvent(0, true);
            }
            break;

            case EventType::MouseButtonReleased: {
                io.AddMouseButtonEvent(0, false);
            }
            break;

            case EventType::MouseMoved: {
                auto mouseMovedEvent = static_cast<MouseMovedEvent&>(e);
                io.AddMousePosEvent(mouseMovedEvent.GetX(), mouseMovedEvent.GetY());
            }
            break;

            default:
                break;
        }
#endif
        if (m_IsBlockEvents)
        {
            ImGuiIO& io = ImGui::GetIO();
            e.Handled |= e.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
            e.Handled |= e.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
        }
    }

    void ImGuiGUISystem::Begin()
    {
#if SOME_ENGINE_RENDER_API_OPENGL || SOME_ENGINE_RENDER_API_OPENGLES
        ImGui_ImplOpenGL3_NewFrame();
#endif
#if SOME_ENGINE_WINDOW_ABSTRACT_GLFW
        ImGui_ImplGlfw_NewFrame();
#elif SOME_ENGINE_WINDOW_ABSTRACT_SDL
        ImGui_ImplSDL2_NewFrame();
#elif SOME_ENGINE_WINDOW_ABSTRACT_EGL && SOME_ENGINE_PLATFORM_ANDROID
        ImGui_ImplAndroid_NewFrame();
#endif
        ImGui::NewFrame();
    }

    void ImGuiGUISystem::End()
    {
        ImGuiIO& io    = ImGui::GetIO();
        io.DisplaySize = ImVec2(m_WindowSys->GetWidth(), m_WindowSys->GetHeight());

        // Rendering
        ImGui::Render();
#if SOME_ENGINE_RENDER_API_OPENGL || SOME_ENGINE_RENDER_API_OPENGLES
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
#if SOME_ENGINE_RENDER_API_OPENGL || SOME_ENGINE_RENDER_API_OPENGLES
#if SOME_ENGINE_WINDOW_ABSTRACT_GLFW
            GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
#elif SOME_ENGINE_WINDOW_ABSTRACT_SDL
            SDL_Window*   window               = SDL_GL_GetCurrentWindow();
            SDL_GLContext backupCurrentContext = SDL_GL_GetCurrentContext();
#endif
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
#if SOME_ENGINE_WINDOW_ABSTRACT_GLFW
            glfwMakeContextCurrent(backupCurrentContext);
#elif SOME_ENGINE_WINDOW_ABSTRACT_SDL
            SDL_GL_MakeCurrent(window, backupCurrentContext);
#endif
#endif
        }
    }
} // namespace SomeEngineRuntime
