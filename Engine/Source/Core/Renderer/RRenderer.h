#pragma once

#include "Core/Core.h"
#include "RRenderAPI.h"

// 因为渲染器类需要存储一些变量，例如场景相关的信息，所以我把渲染器类改成单例类了

namespace Engine {

	class RCamera;
	class RDirectionalLight;
	class RShader;
	class RTexture;
	class WindowResizeEvent;

	class ENGINE_API RRenderer
	{
	private:
		struct FSceneData {
			glm::mat4 ViewProjectionMatrix;
			float DirectionalLightIntensity;
			glm::vec3 DirectionalLightColor;
			glm::vec3 DirectionalLightDirection;
		};
		RRenderAPI* m_RenderAPI;
		FSceneData m_SceneData;
		// 单例
		static RRenderer* s_Instance;
		// 私有构造
		RRenderer(RRenderAPI::EAPI apiType);
	public:
		static inline void Create(RRenderAPI::EAPI type) { if (!s_Instance) s_Instance = new RRenderer(type); }
		static inline RRenderer& Get() {  return *s_Instance; }
		inline RRenderAPI::EAPI GetAPI() { return m_RenderAPI->GetAPI(); }
		inline void SetClearColor(const glm::vec4& color) {
			m_RenderAPI->SetClearColor(color);
		}
		inline void Clear() {
			m_RenderAPI->Clear();
		}
		void BeginScene(RCamera* camera, RDirectionalLight* directionalLight);
		void Submit(RVertexArray* vertexArray, RShader* shader, RTexture* texture, const glm::mat4& transform = glm::mat4(1.f));
		void EndScene();
		// 这里不需要返回bool，因为不是事件分发器调用的，而是直接Application触发窗口大小变化事件时直接调用
		void OnWindwoResize(WindowResizeEvent& e);
	};

}


