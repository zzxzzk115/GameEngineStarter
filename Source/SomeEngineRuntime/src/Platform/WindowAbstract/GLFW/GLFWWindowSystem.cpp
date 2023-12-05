/**
 * @file GLFWWindowSystem.cpp
 * @author Kexuan Zhang (zzxzzk115@gmail.com)
 * @brief
 * @version 0.1.0
 * @date 2023-11-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "SomeEngineRuntime/Platform/WindowAbstract/GLFW/GLFWWindowSystem.h"

#include "SomeEngineRuntime/Core/Event/ApplicationEvent.h"
#include "SomeEngineRuntime/Core/Event/KeyEvent.h"
#include "SomeEngineRuntime/Core/Event/MouseEvent.h"

namespace SomeEngineRuntime
{
    static uint8_t s_glfwWindowCount = 0;

    static void GLFWErrorCallback(int error, const char* description)
    {
        SOME_ENGINE_CORE_ERROR("[GLFWWindowSystem] GLFW Error ({0}) {1}", error, description);
    }

    void GLFWWindowSystem::Init(const WindowSystemInitInfo& initInfo)
    {
        m_Data.Title  = initInfo.Title;
        m_Data.Width  = initInfo.Width;
        m_Data.Height = initInfo.Height;

        SOME_ENGINE_CORE_INFO("[GLFWWindowSystem] Creating window, name: {0}, resolution: {1} x {2}",
                              initInfo.Title,
                              initInfo.Width,
                              initInfo.Height);

        if (s_glfwWindowCount == 0)
        {
            int result = glfwInit();
            SOME_ENGINE_CORE_ASSERT(result, "[GLFWWindowSystem] Could not initialize GLFW!");
            glfwSetErrorCallback(GLFWErrorCallback);
        }

        // Create window
#ifndef NDEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif
#if SOME_ENGINE_RENDER_API_OPENGL
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, SOME_ENGINE_RENDER_API_OPENGL_MIN_MAJOR);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, SOME_ENGINE_RENDER_API_OPENGL_MIN_MINOR);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#elif SOME_ENGINE_RENDER_API_OPENGLES // https://stackoverflow.com/questions/63989357/how-to-use-opengl-es-with-glfw-on-windows
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, SOME_ENGINE_RENDER_API_OPENGLES_MIN_MAJOR);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, SOME_ENGINE_RENDER_API_OPENGLES_MIN_MINOR);
#endif
#if SOME_ENGINE_PLATFORM_DARWIN
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif
        m_Window = glfwCreateWindow((int)initInfo.Width, (int)initInfo.Height, m_Data.Title.c_str(), nullptr, nullptr);
        ++s_glfwWindowCount;

        // Get vid mode
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

        int xPos = (mode->width - initInfo.Width) / 2;
        int yPos = (mode->height - initInfo.Height) / 2;

        // Set window default position (center of screen)
        glfwSetWindowPos(m_Window, xPos, yPos);

        // TODO: Set icon
        // GLFWimage           images[1];
        // RenderPixelColorFormat format;
        // uint32_t            width, height;
        // auto                buffer = ImageTextureImporter::ImportFromPath(
        //     SOME_ENGINE_RELATIVE_PATH("Resources/Textures/SomeEngineLogo.png"), false, format, width, height);
        // images[0].width  = width;
        // images[0].height = height;
        // images[0].pixels = (unsigned char*)buffer.Data;
        // glfwSetWindowIcon(m_Window, 1, images);
        // buffer.Shutdown();

        glfwSetWindowUserPointer(m_Window, &m_Data);

        // Set GLFW callbacks
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Width       = width;
            data.Height      = height;

            WindowResizeEvent event(width, height);
            data.EventCallback(event);
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
            WindowData&      data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.EventCallback(event);
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS: {
                    KeyPressedEvent event(key, 0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT: {
                    KeyPressedEvent event(key, true);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            KeyTypedEvent event(keycode);
            data.EventCallback(event);
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS: {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)xPos, (float)yPos);
            data.EventCallback(event);
        });

        SOME_ENGINE_CORE_INFO("[GLFWWindowSystem] Initialized");
    }

    void GLFWWindowSystem::Shutdown()
    {
        glfwDestroyWindow(m_Window);
        --s_glfwWindowCount;

        if (s_glfwWindowCount == 0)
        {
            glfwTerminate();
        }
    }

    bool GLFWWindowSystem::OnUpdate()
    {
        glfwPollEvents();
        return true;
    }

    void GLFWWindowSystem::MakeCurrentContext() { glfwMakeContextCurrent(m_Window); }

    void GLFWWindowSystem::SwapBuffers() { glfwSwapBuffers(m_Window); }
} // namespace SomeEngineRuntime