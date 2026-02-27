
#include "enginepch.h"
#include "RVertexArray.h"
#include "RRenderer.h"
#include "Platform/OpenGL/ROpenGLVertexArray.h"

namespace Engine {

	RVertexArray* RVertexArray::Create()
	{
		switch (RRenderer::Get().GetAPI()) {
		case RRenderAPI::EAPI::None:
			ENGINE_ERROR("RendererAPI: ERendererAPI::None is not supported!");
			return nullptr;
			break;
		case RRenderAPI::EAPI::OpenGL:
			return new ROpenGLVertexArray();
			break;
		default:
			ENGINE_ERROR("RendererAPI: ::Unknown RendererAPI!");
			return nullptr;
			break;
		}
	}

}
