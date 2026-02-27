#pragma once

#include "Core/Renderer/RGraphicsContext.h"

struct GLFWwindow;

namespace Engine {
	class ROpenGLContext : public RGraphicsContext
	{
	private:
		GLFWwindow* m_Window;
	public:
		ROpenGLContext(GLFWwindow* window);
		// Í¨¹ý GraphicsContext ¼Ì³Ð
		void Init() override;
		void SwapBuffers() override;
	};
}
