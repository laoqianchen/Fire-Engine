
#include "enginepch.h"
#include "CameraController.h"
#include "Renderer/RCamera.h"
#include "Input.h"
#include "KeyCodes.h"
#include "MouseButtonCodes.h"
#include "Core/Events/MouseEvent.h"
#include "Core/Events/ApplicationEvent.h"
#include <glm/glm.hpp>

namespace Engine {

	CameraController* CameraController::s_Instance = nullptr;

	bool CameraController::OnMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		if (e.GetMouseButton() == ENGINE_MOUSE_BUTTON_RIGHT) {
			m_bCanLook = true;
			m_bCanMove = true;
		}
		return false;
	}

	bool CameraController::OnMouseButtonReleased(MouseButtonReleasedEvent& e)
	{
		if (e.GetMouseButton() == ENGINE_MOUSE_BUTTON_RIGHT) {
			m_bCanLook = false;
			m_bCanMove = false;
		}
		return false;
	}

	bool CameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		if (m_bCanMove) {
			m_CameraSpeed = std::clamp(m_CameraSpeed + float(e.GetYOffset()), 1.f, 10.f);
		}
		return false;
	}

	bool CameraController::OnWindowResize(WindowResizeEvent& e)
	{
		return false;
	}

	void CameraController::OnUpdate(float deltaTime)
	{
		if (!m_Camera.lock()) return;  // m_Camera不存在
		// 处理观察
		// 获取两次事件之间Mouse位置的差值
		float deltaX = Input::GetMousePos().first - m_CursorX;
		float deltaY = Input::GetMousePos().second - m_CursorY;
		m_CursorX = Input::GetMousePos().first;
		m_CursorY = Input::GetMousePos().second;
		if (m_bCanLook) {
			const glm::vec3 cameraRot = m_Camera.lock()->GetRotation();
			m_Camera.lock()->SetRotation(glm::vec3(cameraRot.x - deltaY, cameraRot.y - deltaX, 0.f));
		}
		// 处理移动
		if (m_bCanMove) {
			float CameraSpeed = m_CameraSpeed * deltaTime;
			if (Input::IsKeyPressed(ENGINE_KEY_W)) {
				m_Camera.lock()->SetLocation(
					m_Camera.lock()->GetLocation() +
					m_Camera.lock()->GetForwardVector() * CameraSpeed
				);
			}
			if (Input::IsKeyPressed(ENGINE_KEY_A)) {
				m_Camera.lock()->SetLocation(
					m_Camera.lock()->GetLocation() -
					m_Camera.lock()->GetRightVector() * CameraSpeed
				);
			}
			if (Input::IsKeyPressed(ENGINE_KEY_S)) {
				m_Camera.lock()->SetLocation(
					m_Camera.lock()->GetLocation() -
					m_Camera.lock()->GetForwardVector() * CameraSpeed
				);
			}
			if (Input::IsKeyPressed(ENGINE_KEY_D)) {
				m_Camera.lock()->SetLocation(
					m_Camera.lock()->GetLocation() +
					m_Camera.lock()->GetRightVector() * CameraSpeed
				);
			}
			if (Input::IsKeyPressed(ENGINE_KEY_E)) {
				const glm::vec3& CamLoc = m_Camera.lock()->GetLocation();
				m_Camera.lock()->SetLocation(glm::vec3(CamLoc.x, CamLoc.y + CameraSpeed, CamLoc.z));
			}
			if (Input::IsKeyPressed(ENGINE_KEY_Q)) {
				const glm::vec3& CamLoc = m_Camera.lock()->GetLocation();
				m_Camera.lock()->SetLocation(glm::vec3(CamLoc.x, CamLoc.y - CameraSpeed, CamLoc.z));
			}
		}
	}

	void CameraController::OnEvent(Event& e)
	{
		if (!m_Camera.lock()) return;  // m_Camera不存在
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(CameraController::OnMouseButtonPressed));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FN(CameraController::OnMouseButtonReleased));
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(CameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(CameraController::OnWindowResize));
	}
}