#pragma once

#include "Core/Renderer/RBuffer.h"

namespace Engine{
	class ROpenGLVertexBuffer : public RVertexBuffer {
	private:
		uint32_t m_RendererID;
		RBufferLayout m_Layout;
	public:
		ROpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~ROpenGLVertexBuffer();

		// 通过 RVertexBuffer 继承
		void Bind() const override;
		void UnBind() const override;
		inline const RBufferLayout& GetLayout() const override { return m_Layout; }
		inline void SetLayout(const RBufferLayout& layout) override { m_Layout = layout; }
	};

	class ROpenGLIndexBuffer : public RIndexBuffer {
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;  // 有多少个索引在这里面
	public:
		ROpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~ROpenGLIndexBuffer();

		// 通过 RVertexBuffer 继承
		void Bind() const override;
		void UnBind() const override;
		uint32_t GetCount() const override { return m_Count; }
	};
}