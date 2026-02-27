
#include "enginepch.h"
#include "RLight.h"
#include <glm/gtc/quaternion.hpp>

namespace Engine {
	const glm::vec3& RLight::GetForwardVector()
	{
		// 获取目标朝向0.f, 0.f, -1.f经过Rotation旋转后的值
		glm::quat q = glm::quat(glm::radians(m_Rotation));
		return glm::normalize(q * glm::vec3(0.f, 0.f, -1.f));
	}
	const glm::vec3& RLight::GetRightVector()
	{
		glm::quat q = glm::quat(glm::radians(m_Rotation));
		return glm::normalize(q * glm::vec3(1.f, 0.f, 0.f));
	}
	const glm::vec3& RLight::GetUpVector()
	{
		glm::quat q = glm::quat(glm::radians(m_Rotation));
		return glm::normalize(q * glm::vec3(0.f, 1.f, 0.f));
	}
}
