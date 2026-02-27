
#include "enginepch.h"
#include "WindowsInput.h"

#include <GLFW/glfw3.h>
#include "Core/Application.h"
#include "Core/Window.h"

namespace Engine {

	Input* Input::s_Instance = new WindowsInput();  // 这个类完全就是一个全局的实例，不依赖于其他任何东西，所以这里直接实例化一个即可，没必要在其他地方实例化这个单例

	bool WindowsInput::IsKeyPressedImpl(int keycode){
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}
	std::pair<double, double> WindowsInput::GetMousePosImpl()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return	{ xpos, ypos };
	}
}