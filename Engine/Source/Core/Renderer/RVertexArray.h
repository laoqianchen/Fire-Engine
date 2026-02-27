#pragma once

#include "Core/Core.h"
#include "Core/Renderer/RBuffer.h"
#include <memory>

namespace Engine {
	
	class ENGINE_API RVertexArray {
	public:
		virtual ~RVertexArray() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void AddVertexBuffer(const TSharedPtr<RVertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const TSharedPtr<RIndexBuffer>& indexBuffer) = 0;

		virtual const  std::vector<TSharedPtr<RVertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const TSharedPtr<RIndexBuffer>& GetIndexBuffer() const = 0;

		static RVertexArray* Create();
	};

}