#pragma once

#include "Core/Core.h"
#include <string>

namespace Engine {
	class ENGINE_API RTexture
	{
	public:
		virtual ~RTexture() {}  // 最高的父类必须开一个虚析构，子类析构才会起作用
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		virtual unsigned int GetChannels() const = 0;
		virtual void Bind(unsigned int slot = 0) const = 0;
	};

	class ENGINE_API RTexture2D : public RTexture {
	public:
		virtual ~RTexture2D() {}
		// 2D纹理工厂方法
		static RTexture2D* Create(const std::string& path);
	};
}

