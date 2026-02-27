#pragma once

#include "Core/Core.h"
#include <glm/glm.hpp>

namespace Engine {

	class ENGINE_API RCamera {
	protected:
		// glm不会自动初始化，所以记得自己手动初始化一下
		glm::mat4 m_ProjectionMatrix;  // 投影矩阵
		glm::mat4 m_ViewMatrix;  // 视图矩阵
		glm::mat4 m_ViewProjectionMatrix;  // 视图投影矩阵（缓存一下方便上传到着色器）
		// 大部分游戏引擎中Location都是世界坐标
		glm::vec3 m_Location = glm::vec3(0.f);  // 相机位置
		// 大部分游戏引擎中Rotation都是局部坐标，虽然轴的方向是世界方向，但是轴的位置一般在物品的几何中心
		glm::vec3 m_Rotation = glm::vec3(0.f);  // 使用欧拉角来描述旋转（直观方便），运算时会转换为四元数做运算，避免万向节死锁死锁问题
	private:
		void UpdateViewMatrix();
	public:
		const glm::vec3& GetLocation() const { return m_Location; }
		void SetLocation(const glm::vec3& Location) { m_Location = Location; UpdateViewMatrix(); }
		const glm::vec3& GetRotation() const { return m_Rotation; }
		void SetRotation(const glm::vec3& rotation) { m_Rotation = rotation; UpdateViewMatrix(); }
		const glm::vec3& GetForwardVector();
		const glm::vec3& GetRightVector();
		const glm::vec3& GetUpVector();
		const glm::mat4& GetViewMatrix() { return m_ViewMatrix; }
		const glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; }
		const glm::mat4& GetViewProjectionMatrix() { return m_ViewProjectionMatrix; }
	};

	// 正交相机
	class ENGINE_API ROrthographicCamera : public RCamera{
	public:
		ROrthographicCamera(float left, float right, float bottom, float top);
	};

	// 透视相机
	class ENGINE_API RPerspectiveCamera : public RCamera {
	public:
		RPerspectiveCamera(float fovDegrees, float aspectRatio, float nearPlane, float farPlane);
	};


}


