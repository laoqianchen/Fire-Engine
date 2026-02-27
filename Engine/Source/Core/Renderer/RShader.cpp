
#include "enginepch.h"
#include "RShader.h"
#include "Platform/OpenGL/ROpenGLShader.h"
#include "RRenderer.h"

namespace Engine {
	RShader* RShader::Create(const std::string& filePath)
	{
		switch (RRenderer::Get().GetAPI())
		{
		case RRenderAPI::EAPI::None:
			ENGINE_ERROR("RendererAPI: ERendererAPI::None is not supported!");
			return nullptr;
			break;
		case RRenderAPI::EAPI::OpenGL:
			// 构建一个OpenGL着色器并返回回去
			return new ROpenGLShader(filePath);
			break;
		default:
			ENGINE_ERROR("RendererAPI: ::Unknown RendererAPI!");
			return nullptr;
			break;
		}
	}

	RShader* RShader::Create(const std::string& name, const std::string& filePath)
	{
		switch (RRenderer::Get().GetAPI())
		{
		case RRenderAPI::EAPI::None:
			ENGINE_ERROR("RendererAPI: ERendererAPI::None is not supported!");
			return nullptr;
			break;
		case RRenderAPI::EAPI::OpenGL:
			// 构建一个OpenGL着色器并返回回去
			return new ROpenGLShader(name, filePath);
			break;
		default:
			ENGINE_ERROR("RendererAPI: ::Unknown RendererAPI!");
			return nullptr;
			break;
		}
	}
	RShader* RShader::Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (RRenderer::Get().GetAPI())
		{
		case RRenderAPI::EAPI::None:
			ENGINE_ERROR("RendererAPI: ERendererAPI::None is not supported!");
			return nullptr;
			break;
		case RRenderAPI::EAPI::OpenGL:
			// 构建一个OpenGL着色器并返回回去
			return new ROpenGLShader(name, vertexSource, fragmentSource);
			break;
		default:
			ENGINE_ERROR("RendererAPI: ::Unknown RendererAPI!");
			return nullptr;
			break;
		}
	}

	RShaderLibrary* RShaderLibrary::s_Instance = nullptr;

	bool RShaderLibrary::IsShaderExist(const std::string& name)
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}
	void RShaderLibrary::AddShader(RShader* shader)
	{
		const std::string& name = shader->GetName();
		ENGINE_ASSERT(!IsShaderExist(name), "Shader already exist!");
		m_Shaders[name] = TSharedPtr<RShader>(shader);
	}
	void RShaderLibrary::AddShaderFromFile(const std::string& filePath)
	{
		RShader* shader = RShader::Create(filePath);
		AddShader(shader);
	}
	TSharedPtr<RShader> RShaderLibrary::GetShader(const std::string& name)
	{
		ENGINE_ASSERT(IsShaderExist(name), "Shader not exist!");
		return m_Shaders[name];
	}
}
