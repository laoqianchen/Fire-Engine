#pragma once

#include "Core/Core.h"

namespace Engine {
	class RGraphicsContext {
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}