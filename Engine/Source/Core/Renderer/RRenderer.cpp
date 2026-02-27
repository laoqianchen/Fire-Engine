
#include "enginepch.h"
#include "RRenderer.h"
#include "Platform/OpenGL/ROpenGLRenderAPI.h"
#include "RVertexArray.h"
#include "RShader.h"
#include "RTexture.h"
#include "RCamera.h"
#include "RLight.h"
#include "Core/Events/ApplicationEvent.h"

namespace Engine {

	RRenderer* RRenderer::s_Instance = nullptr;

	RRenderer::RRenderer(RRenderAPI::EAPI apiType)
	{
		// 创建对应的渲染API
		switch (apiType)
		{
		case Engine::RRenderAPI::EAPI::None:
			break;
		case Engine::RRenderAPI::EAPI::OpenGL:
			m_RenderAPI = new ROpenGLRenderAPI(apiType);
			break;
		default:
			break;
		}
		if (m_RenderAPI) m_RenderAPI->Init();
	}

	void RRenderer::BeginScene(RCamera* camera, RDirectionalLight* directionalLight)
	{
		// 确保着色器能正确获取统一变量（
		// 包括所使用的环境贴图，
		// 包括相机细节（视图矩阵，投影矩阵，相机位置，相机朝向）
		// 光源等等
		// ）
		// 这堆统一变量信息将在BeginScene时设置，并最终存储在当前的场景中
		m_SceneData.ViewProjectionMatrix = camera->GetViewProjectionMatrix();
		m_SceneData.DirectionalLightIntensity = directionalLight->GetIntensity();
		m_SceneData.DirectionalLightColor = directionalLight->GetColor();
		m_SceneData.DirectionalLightDirection = directionalLight->GetForwardVector();
	}

	void RRenderer::Submit(RVertexArray* vertexArray, RShader* shader, RTexture* texture, const glm::mat4& transform)
	{
		vertexArray->Bind();
		shader->Bind();
		if (texture) {
			unsigned int slot = 0;
			texture->Bind(slot);
			// 上传纹理到着色器
			shader->UploadUniformInt("u_Texture", slot);  // 上传从哪个槽位采样纹理
		}
		// 上传视图投影矩阵到着色器（整个场景都是这个值）
		shader->UploadUniformMat4("u_ViewProjectionMatrix", m_SceneData.ViewProjectionMatrix);
		// 上传模型变换矩阵到着色器
		shader->UploadUniformMat4("u_ModelMatrix", transform);
		// 上传定向光源相关信息到着色器
		shader->UploadUniformFloat("u_DirectionalLightIntensity", m_SceneData.DirectionalLightIntensity);
		shader->UploadUniformFloat3("u_DirectionalLightColor", m_SceneData.DirectionalLightColor);
		shader->UploadUniformFloat3("u_DirectionalLightDirection", m_SceneData.DirectionalLightDirection);
		m_RenderAPI->DrawCall(vertexArray);
	}

	void RRenderer::EndScene()
	{
	}

	void RRenderer::OnWindwoResize(WindowResizeEvent& e)
	{
		m_RenderAPI->SetViewport(0, 0, e.GetWidth(), e.GetHeight());
	}
}