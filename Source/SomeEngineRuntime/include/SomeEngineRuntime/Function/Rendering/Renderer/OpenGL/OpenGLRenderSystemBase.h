#pragma once

#include "SomeEngineRuntime/Function/Rendering/RenderSystem.h"
#include "SomeEngineRuntime/Function/Rendering/Renderer/OpenGL/OpenGLContextBase.h"

namespace SomeEngineRuntime
{
    class OpenGLRenderSystemBase : public RenderSystem
    {
    public:
        virtual void Init(const RenderSystemInitInfo& initInfo);
        virtual void Update(float deltaTime);
        virtual void Shutdown();
        virtual void Present();
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

    private:
        Ref<OpenGLContextBase> m_Context;
    };
} // namespace SomeEngineRuntime
