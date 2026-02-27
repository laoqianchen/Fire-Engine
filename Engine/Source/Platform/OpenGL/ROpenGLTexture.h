#pragma once

#include "Core/Renderer/RTexture.h"

namespace Engine {
    class ROpenGLTexture2D : public RTexture2D
    {
    private:
        // 保留Texture对应的路径，方便debug，热重载...
        // 其实后续如果做一个资源管理器的话（维护路径与实例的关系），就完全不需要把路径保存在这里了
        std::string m_Path;
        // 这几个参数用int，是因为stb_image获取的时候是返回的int
        int m_Width;
        int m_Height;
        int m_Channels;
        unsigned int m_RendererID;
    public:
        ROpenGLTexture2D(const std::string& path);
        virtual ~ROpenGLTexture2D();

        // 通过 RTexture2D 继承
        unsigned int GetWidth() const override { return m_Width; }
        unsigned int GetHeight() const override { return m_Height; }
        unsigned int GetChannels() const override { return m_Channels; }
        void Bind(unsigned int slot = 0) const override;
    };
}


