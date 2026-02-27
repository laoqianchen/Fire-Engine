#pragma once

#include "Core/Renderer/RVertexArray.h"

namespace Engine {

	class RVertexBuffer;
	class RIndexBuffer;

	class ROpenGLVertexArray : public RVertexArray
	{
	private:
		unsigned int m_RendererID;
		std::vector<TSharedPtr<RVertexBuffer>> m_VertexBuffers;  // 保存了我们所有放入的顶点缓冲区的引用关系
		TSharedPtr<RIndexBuffer> m_IndexBuffer;  // 
	public:
		ROpenGLVertexArray();
		virtual ~ROpenGLVertexArray();

		// 通过 RVertexArray 继承
		void Bind() const override;
		void UnBind() const override;

		void AddVertexBuffer(const TSharedPtr<RVertexBuffer>& vertexBuffer) override;
		void SetIndexBuffer(const TSharedPtr<RIndexBuffer>& indexBuffer) override;

		const std::vector<TSharedPtr<RVertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }
		const TSharedPtr<RIndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }
	};

}

