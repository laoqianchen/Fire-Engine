#pragma once


#include "Core/Core.h"

namespace Engine {

	class Event;
	class MouseButtonPressedEvent;
	class MouseButtonReleasedEvent;
	class MouseMovedEvent;
	class MouseScrolledEvent;
	class WindowResizeEvent;
	class RCamera;

	class ENGINE_API CameraController
	{
	private:
		TWeakPtr<RCamera> m_Camera;  // Camera是用户创建的，用户的应用程序负责Camera的生命周期
		static CameraController* s_Instance;  // 暂时做成一个单例类，因为一般来说玩家全局只能控制一个相机
		float m_CameraSpeed = 1.f;

		float m_CursorX = 0.f;
		float m_CursorY = 0.f;
		bool m_bCanLook = false;
		bool m_bCanMove = false;
	private:
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleased(MouseButtonReleasedEvent& e);
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	public:
		static void Create() { if (!s_Instance) s_Instance = new CameraController; }
		static CameraController* Get() { return s_Instance; }
		void SetCamera(const TSharedPtr<RCamera>& camera) { m_Camera = camera; m_CameraSpeed = 1.f; }  // C++中弱指针只能从共享指针转换过来
		void OnUpdate(float deltaTime);
		void OnEvent(Event& e);
	};
}
