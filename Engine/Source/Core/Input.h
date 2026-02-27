#pragma once

#include "Core/Core.h"

namespace Engine {
	class ENGINE_API Input {
	private:
		static Input* s_Instance;
	protected:
		// 每个平台需要实现的内容
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<double, double> GetMousePosImpl() = 0;
	public:
		static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		static std::pair<double, double> GetMousePos() { return s_Instance->GetMousePosImpl(); }
	};
}