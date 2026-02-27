
#include "enginepch.h"
#include "ROpenGLRenderAPI.h"
#include "Core/Renderer/RVertexArray.h"
#include <glad/glad.h>

namespace Engine {
	void ROpenGLRenderAPI::Init()
	{
		// 开启混合
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  // 原颜色与目标颜色的混合权重
		// 开启深度测试
		glEnable(GL_DEPTH_TEST);
	}
	void ROpenGLRenderAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}
	void ROpenGLRenderAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void ROpenGLRenderAPI::SetViewport(unsigned int x, unsigned y, unsigned int width, unsigned int height)
	{
		glViewport(x, y, width, height);
	}
	void ROpenGLRenderAPI::DrawCall(RVertexArray* vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}