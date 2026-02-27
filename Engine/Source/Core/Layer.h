#pragma once

#include "Core.h"
#include <string>

namespace Engine {

	class Event;

	class ENGINE_API Layer {
	protected:
		std::string m_DebugName;
	public:
		Layer(const std::string& name = "Layer") : m_DebugName(name) {}
		virtual ~Layer() {}

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate(float deltaTime) {};
		virtual void OnEvent(Event& e) {};
		virtual void OnImGuiRender() {};

		inline const std::string& GetName() const { return m_DebugName; }
	};
}
