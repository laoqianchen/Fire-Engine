#pragma once

#include "Engine.h"

class MyGameLayer : public Engine::Layer {
private:
	// 纹理
	Engine::TSharedPtr<Engine::RTexture> m_WoodTexture;
	Engine::TSharedPtr<Engine::RTexture> m_MetalTexture;
	Engine::TSharedPtr<Engine::RTexture> m_WaterTexture;
	Engine::TSharedPtr<Engine::RTexture> m_StoneTexture;
	Engine::TSharedPtr<Engine::RTexture> m_PaperTexture;
	// 顶点数组
	Engine::TSharedPtr<Engine::RVertexArray> m_VertexArray;
	// 相机
	Engine::TSharedPtr<Engine::RCamera> m_Camera;
	float m_CameraSpeed = 1.f;  // 相机移动速度
	// 定向光（太阳）
	Engine::TSharedPtr<Engine::RDirectionalLight> m_DirectionalLight;
	// 定向光参数
	float m_DirectionalLightIntensity = 1.f;
	glm::vec3 m_DirectionalLightColor = glm::vec3(1.f);
	glm::vec3 m_DirectionalLightRotation = glm::vec3(-45.f, 45.f, 0.f);
	// 昼夜系统
	float m_DayTime = 6.0f; // 当前是几点（按小时来算）
	float m_DayLength = 24.f;  // 一天的时长
	float m_RealTimePerCycle = 180.f;  // 现实世界一整天对应秒数，例如 60 秒 = 游戏 24 小时
	bool m_bIsRunDayCycle = true;  // 是否开启日夜循环
public:
	MyGameLayer();
	void OnUpdate(float deltaTime) override;
	void OnEvent(Engine::Event& e) override;
	void OnImGuiRender() override;
};

class MyGameInOneHour : public Engine::Application {
public:
	MyGameInOneHour() {
		PushLayer(new MyGameLayer);
	}
};

Engine::Application* Engine::CreateApplication() {
	return new MyGameInOneHour();
}