#include "enginepch.h"
#include "WindowsWindow.h"

#include "Core/Events/ApplicationEvent.h"
#include "Core/Events/KeyEvent.h"
#include "Core/Events/MouseEvent.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Platform/OpenGL/ROpenGLContext.h"

namespace Engine {
	
	// 窗口只需要初始化一次，但是我们可以创建多个窗口
	static bool s_GLFWInitialed = false;

	static void GLFWErrorCallback(int error, const char* description) {
		ENGINE_ERROR("GLFW错误{}：{}", error, description);
	}

	void WindowsWindow::Init(const FWindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		ENGINE_INFO("Create Window: {}({}x{})", m_Data.Title, m_Data.Width, m_Data.Height);
	
		if (!s_GLFWInitialed) {
			// 如果还未初始化，那么进行一次初始化
			int success = glfwInit();
			ENGINE_ASSERT(success, "无法初始化GLFW");
			// 绑定JLW错误回调
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialed = true;
		}

		m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		// 创建上下文：
		m_Context = new ROpenGLContext(m_Window);
		m_Context->Init();

		// 把指针挂到 GLFW 的 GLFWwindow 对象上，供回调函数在“无 this 指针”的情况下取回上下文。也就是说回调函数（比如按键回调）中是可以访问到这个指针的
		glfwSetWindowUserPointer(m_Window, &m_Data); 
		SetVSync(true);

		// 设置GLFW的回调函数
		// 窗口大小改变事件
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
				FWindowData* data = (FWindowData*)glfwGetWindowUserPointer(window);
				data->Width = width;
				data->Height = height;
				WindowResizeEvent event(width, height);
				data->EventCallback(event);
			});
		// 窗口关闭事件
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
				FWindowData* data = (FWindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data->EventCallback(event);
			});
		// 按键事件（这个key是GLFW专有的，我们需要把他转换到自己的键码上，我们不想把引擎绑死GLFW）
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
				FWindowData* data = (FWindowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
				case GLFW_PRESS: {
					KeyPressedEvent event(key, 0);
					data->EventCallback(event);
					break;
				}
				case GLFW_REPEAT: {
					// GLFW没有提供获取按键重复次数的方法，所以这里暂定为1
					KeyPressedEvent event(key, 1);
					data->EventCallback(event);
					break;
				}
				case GLFW_RELEASE: {
					KeyReleasedEvent event(key);
					data->EventCallback(event);
					break;
				}
				default:
					break;
				}
			});
		// 按键键入事件
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) {
				FWindowData* data = (FWindowData*)glfwGetWindowUserPointer(window);
				KeyTypedEvent event(keycode);
				data->EventCallback(event);
			});
		// 鼠标按钮事件（这个button是GLFW专有的，我们需要把他转换到自己的键码上，我们不想把引擎绑死GLFW）
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
				FWindowData* data = (FWindowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
				case GLFW_PRESS: {
					MouseButtonPressedEvent event(button);
					data->EventCallback(event);
					break;
				}
				case GLFW_RELEASE: {
					MouseButtonReleasedEvent event(button);
					data->EventCallback(event);
					break;
				}
				default:
					break;
				}
			});
		// 鼠标滚动事件
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) {
				FWindowData* data = (FWindowData*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent event(xoffset, yoffset);
				data->EventCallback(event);
			});
		// 鼠标光标位置事件
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) {
				FWindowData* data = (FWindowData*)glfwGetWindowUserPointer(window);
				MouseMovedEvent event(xpos, ypos);
				data->EventCallback(event);
			});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	WindowsWindow::WindowsWindow(const FWindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}
		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}
