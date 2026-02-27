#pragma once

#include "Core.h"
#include <memory>  // 因为这个头文件会被用户项目包含，用户项目不一定预编译了这个文件，所以要手动包含一次
#include <vector>  // 因为这个头文件会被用户项目包含，用户项目不一定预编译了这个文件，所以要手动包含一次
#include <chrono>  // 获取当前时间，计算DeltaTime
#include "Core/Renderer/RCamera.h"
#include "LayerStack.h"

namespace Engine {

	class Window;
	class Event;
	class WindowCloseEvent;
	class WindowResizeEvent;
	class Layer;
	class ImGuiLayer;
	class RCamera;

	class ENGINE_API Application{
	private:
		// Application是一个单例
		static Application* s_Instance;
		// 窗口
		TUniquePtr<Window> m_Window;
		// UI层
		TUniquePtr<ImGuiLayer> m_ImGuiLayer;

		// 层堆栈
		LayerStack m_LayerStack;
		
		bool m_bIsRunning = true;
		bool m_bIsMinimized = false;
		std::chrono::steady_clock::time_point m_LastFrameTime;  // 用于测量真实的帧率

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	public:	
		Application();
		virtual ~Application();
	public:
		void Run();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	};
	// 在用户程序中做具体实现
	Application* CreateApplication();
}


