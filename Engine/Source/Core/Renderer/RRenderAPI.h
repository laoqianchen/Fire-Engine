#pragma once

#include <glm/glm.hpp>
// RenderAPI是一个接口，会根据具体情况来做对应的实现

namespace Engine {

	class RVertexArray;

	class RRenderAPI
	{
	public:
		// 可选的渲染API类型
		enum class EAPI {
			None,
			OpenGL
		};
		EAPI m_API;
	public:
		RRenderAPI(EAPI renderAPI) : m_API(renderAPI) {}
		virtual void Init() = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;
		virtual void SetViewport(unsigned int x, unsigned y, unsigned int width, unsigned int height) = 0;
		virtual void DrawCall(RVertexArray* vertexArray) = 0;
		inline EAPI GetAPI() { return m_API; }
	};
}


