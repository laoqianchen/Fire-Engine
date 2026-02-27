#pragma once

#include "Core/Input.h"

namespace Engine {
	class WindowsInput : public Input
	{
	protected:
		// Í¨¹ý Input ¼Ì³Ð
		bool IsKeyPressedImpl(int keycode) override;
		bool IsMouseButtonPressedImpl(int button) override;
		std::pair<double, double> GetMousePosImpl() override;
	};
}


