
#include "enginepch.h"
#include "RTexture.h"
#include "Platform/OpenGL/ROpenGLTexture.h"
#include "RRenderer.h"

namespace Engine {
	RTexture2D* RTexture2D::Create(const std::string& path)
	{
		switch (RRenderer::Get().GetAPI())
		{
		case RRenderAPI::EAPI::None:
			ENGINE_ERROR("RendererAPI: ERendererAPI::None is not supported!");
			return nullptr;
			break;
		case RRenderAPI::EAPI::OpenGL:
			return new ROpenGLTexture2D(path);
			break;
		default:
			ENGINE_ERROR("RendererAPI: ::Unknown RendererAPI!");
			return nullptr;
			break;
		}
	}
}