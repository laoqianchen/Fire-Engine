#include "enginepch.h"
#include "ROpenGLContext.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Engine {
	ROpenGLContext::ROpenGLContext(GLFWwindow* window) : m_Window(window){
		ENGINE_ASSERT(window, "窗口为空，无法使用窗口创建上下文");
	}
	void ROpenGLContext::Init(){
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ENGINE_ASSERT(status, "Glad初始化失败");
		// 查询使用的是什么GPU上的OpenGL进行渲染
		ENGINE_INFO("OpenGL Vendor: {}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
		ENGINE_INFO("OpenGL Renderer: {}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
		ENGINE_INFO("OpenGL Version: {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
	}
	void ROpenGLContext::SwapBuffers(){
		glfwSwapBuffers(m_Window);
	}
}
