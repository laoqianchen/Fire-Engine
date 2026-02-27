
#include "enginepch.h"
#include "RBuffer.h"
#include "RRenderer.h"

#include "Platform/OpenGL/ROpenGLBuffer.h"

namespace Engine {
	RVertexBuffer* RVertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (RRenderer::Get().GetAPI())
		{
		case RRenderAPI::EAPI::None:
			ENGINE_ERROR("RendererAPI: ERendererAPI::None is not supported!");
			return nullptr;
			break;
		case RRenderAPI::EAPI::OpenGL:
			// 构建一个OpenGL顶点缓冲区返回回去
			return new ROpenGLVertexBuffer(vertices, size);
			break;
		default:
			ENGINE_ERROR("RendererAPI: ::Unknown RendererAPI!");
			return nullptr;
			break;
		}
	}
	RIndexBuffer* RIndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (RRenderer::Get().GetAPI())
		{
		case RRenderAPI::EAPI::None:
			ENGINE_ERROR("RendererAPI: ERendererAPI::None is not supported!");
			return nullptr;
			break;
		case RRenderAPI::EAPI::OpenGL:
			// 构建一个OpenGL顶点缓冲区返回回去
			return new ROpenGLIndexBuffer(indices, size);
			break;
		default:
			ENGINE_ERROR("RendererAPI: ::Unknown RendererAPI!");
			return nullptr;
			break;
		}
	}
}