/**
 * @file OpenGLESContext.h
 * @author Kexuan Zhang (zzxzzk115@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-11-29
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include "SomeEngineRuntime/Function/Rendering/Renderer/OpenGL/OpenGLContextBase.h"

namespace SomeEngineRuntime
{
    class OpenGLESContext : public OpenGLContextBase
    {
    public:
        virtual int                LoadGL() override final;
        inline virtual int         GetMinMajor() override final { return SOME_ENGINE_RENDER_API_OPENGLES_MIN_MAJOR; }
        inline virtual int         GetMinMinor() override final { return SOME_ENGINE_RENDER_API_OPENGLES_MIN_MINOR; }
        virtual const std::string& GetName() override final { return m_Name; }

    private:
        std::string m_Name = "OpenGL";
    };
} // namespace SomeEngineRuntime
