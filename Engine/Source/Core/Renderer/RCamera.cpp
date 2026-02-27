
#include "enginepch.h"
#include "RCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Engine {
	void RCamera::UpdateViewMatrix()
	{
		// glm的矩阵乘法是右结合的，所以写的时候要z*y*x
		// 这些API右老遗留问题，必须第一个参数传一个单位矩阵进去，这实际上表示的是，在原有矩阵的基础上，附加一个变换
		glm::mat4 transform = glm::translate(glm::mat4(1.f), m_Location) *
			glm::rotate(glm::mat4(1.f), glm::radians(m_Rotation.z), glm::vec3(0.f, 0.f, 1.f)) *
			glm::rotate(glm::mat4(1.f), glm::radians(m_Rotation.y), glm::vec3(0.f, 1.f, 0.f)) *
			glm::rotate(glm::mat4(1.f), glm::radians(m_Rotation.x), glm::vec3(1.f, 0.f, 0.f));
		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	const glm::vec3& RCamera::GetForwardVector()
	{
		glm::quat q = glm::quat(glm::radians(m_Rotation));
		return glm::normalize(q * glm::vec3(0.f, 0.f, -1.f));
	}
	const glm::vec3& RCamera::GetRightVector()
	{
		glm::quat q = glm::quat(glm::radians(m_Rotation));
		return glm::normalize(q * glm::vec3(1.f, 0.f, 0.f));
	}
	const glm::vec3& RCamera::GetUpVector()
	{
		glm::quat q = glm::quat(glm::radians(m_Rotation));
		return glm::normalize(q * glm::vec3(0.f, 1.f, 0.f));
	}
	ROrthographicCamera::ROrthographicCamera(float left, float right, float bottom, float top)
	{
		m_ViewMatrix = glm::mat4(1.f);
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.f, 1.f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	RPerspectiveCamera::RPerspectiveCamera(float fovDegrees, float aspectRatio, float nearPlane, float farPlane)
	{
		m_ViewMatrix = glm::mat4(1.f);
		m_ProjectionMatrix = glm::perspective(glm::radians(fovDegrees), aspectRatio, nearPlane, farPlane);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}