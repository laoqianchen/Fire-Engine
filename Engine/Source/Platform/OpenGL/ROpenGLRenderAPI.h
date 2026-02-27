#pragma once

#include "Core/Renderer/RRenderAPI.h"

namespace Engine {
    class ROpenGLRenderAPI : public RRenderAPI
    {
    public:
        ROpenGLRenderAPI(EAPI apiType) : RRenderAPI(apiType) {}
        // Í¨¹ý RRenderAPI ¼Ì³Ð
        void Init() override;
        void SetClearColor(const glm::vec4& color) override;
        void Clear() override;
        void SetViewport(unsigned int x, unsigned y, unsigned int width, unsigned int height) override;
        void DrawCall(RVertexArray* vertexArray) override;
    };
}