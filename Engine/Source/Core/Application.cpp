
#include "enginepch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Layer.h"
#include "ImGui/ImGuiLayer.h"
#include "Window.h"
#include "Input.h"
#include "glm/glm.hpp"
#include "Core/Renderer/RRenderer.h"
#include "Core/Renderer/RShader.h"
#include "Core/CameraController.h"

namespace Engine {

	Application* Application::s_Instance = nullptr;

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_bIsRunning = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0) {
			// 说明此时窗口最小化了
			m_bIsMinimized = true;
			return false;
		}
		m_bIsMinimized = false;
		// 调用渲染器的OnWindowResize函数，更新Viewport
		RRenderer::Get().OnWindwoResize(e);
		return false;
	}

	Application::Application()
	{
		ENGINE_ASSERT(!s_Instance, "应用程序单例已经存在，无法再次实例化");
		s_Instance = this;
		m_Window = TUniquePtr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = std::make_unique<ImGuiLayer>();
		PushOverlay(m_ImGuiLayer.get());

		// 创建渲染器单例
		RRenderer::Create(Engine::RRenderAPI::EAPI::OpenGL);

		// 创建着色器库单例
		RShaderLibrary::Create();

		// 创建相机控制器单例
		CameraController::Create();
	}
	Application::~Application()
	{
		delete m_Window.get();  // m_Window因为不明原因打死都不会自动析构，为此我只能在这里采取强硬手段
	}
	void Application::Run()
	{
		while (m_bIsRunning) {

			std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
			std::chrono::duration<float> delta = now - m_LastFrameTime;
			m_LastFrameTime = now;
			float deltaTime = delta.count(); // 秒

			// 最小化之后不应该更新各种层，这些层是最密集DrawCall的地方
			if (!m_bIsMinimized) {
				// 相机控制器更新（实现了默认的相机操作方式）
				CameraController::Get()->OnUpdate(deltaTime);
				// 从前向后处理所有层的更新
				for (Layer* layer : m_LayerStack) {
					layer->OnUpdate(deltaTime);
				}
			}
			// ImGui也要持续更新，否则拖出去的ImGui一旦缩小窗口后就都没反应了
			m_ImGuiLayer->BeginFrame();
			for (Layer* layer : m_LayerStack) {
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->EndFrame();

			// 窗口更新（最小化了也得跑窗口更新（至少glfwPollEvents要执行，否则恢复都恢复不了））
			m_Window->OnUpdate();
		}
	}
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

		// ENGINE_TRACE(e.ToString());

		// 相机控制器处理事件
		CameraController::Get()->OnEvent(e);

		// 从后往前处理所有层的事件
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			// 如果事件被成功处理，那么不会继续传递到下一层
			if (e.IsHandled()) break;
		}
	}
	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}
	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}
}