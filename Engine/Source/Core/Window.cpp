#include "enginepch.h"
#include "Window.h"
#include "Platform/Windows/WindowsWindow.h"

namespace Engine {
	Window* Window::Create(const FWindowProps& props)
	{
		return new WindowsWindow(props);
	}
}

