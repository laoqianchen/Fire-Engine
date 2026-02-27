#pragma once

#include "Core/Layer.h"
#include "Core/Events/KeyEvent.h"
#include "Core/Events/MouseEvent.h"
#include "Core/Events/ApplicationEvent.h"
#include "imgui.h"

namespace Engine {

	class Event;

	class ENGINE_API ImGuiLayer : public Layer {
	private:
		double m_LastTime = 0.f;  // 用来计算DeltaTime的
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void BeginFrame();  // 开启一个ImGuiFrame
		void EndFrame();  // 结束一个ImGuiFrame
	};
}