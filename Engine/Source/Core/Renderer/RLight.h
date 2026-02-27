#pragma once

#include "Core/Core.h"
#include <glm/glm.hpp>

namespace Engine {

	class ENGINE_API RLight
	{
	protected:
		// 大部分游戏引擎中Location都是世界坐标
		glm::vec3 m_Location = glm::vec3(0.f);  // 相机位置
		// 大部分游戏引擎中Rotation都是局部坐标，虽然轴的方向是世界方向，但是轴的位置一般在物品的几何中心
		glm::vec3 m_Rotation = glm::vec3(0.f);  // 使用欧拉角来描述旋转（直观方便），运算时会转换为四元数做运算，避免万向节死锁死锁问题
		// 光源相关参数
		float m_Intensity = 1000.f;
		glm::vec3 m_Color = glm::vec3(1.f);
	public:
		const glm::vec3& GetLocation() const { return m_Location; }
		void SetLocation(const glm::vec3& Location) { m_Location = Location; }
		const glm::vec3& GetRotation() const { return m_Rotation; }
		virtual void SetRotation(const glm::vec3& rotation) { m_Rotation = rotation; }
		const glm::vec3& GetForwardVector();
		const glm::vec3& GetRightVector();
		const glm::vec3& GetUpVector();
		const float GetIntensity() const { return m_Intensity; }
		void SetIntensity(float intensity) { m_Intensity = intensity; }
		const glm::vec3& GetColor() const { return m_Color; }
		void SetColor(const glm::vec3& color) { m_Color = color; }
	};

	class ENGINE_API RDirectionalLight : public RLight {
	public:
	};
}


