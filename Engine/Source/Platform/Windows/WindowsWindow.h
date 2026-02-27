#pragma once

#include "Core/window.h"

struct GLFWwindow;

namespace Engine {
	// Windows平台下的Window窗口实现
	class RGraphicsContext;

	class WindowsWindow : public Window{
	private:
		GLFWwindow* m_Window;
		RGraphicsContext* m_Context;  // 上下文

		struct FWindowData {
			std::string Title;
			unsigned int Width;
			unsigned int Height;
			bool VSync;
			EventCallbackFn EventCallback;
		};
		FWindowData m_Data;
	private:
		virtual void Init(const FWindowProps& props);
		virtual void Shutdown();
	public:
		WindowsWindow(const FWindowProps& props);
		virtual ~WindowsWindow();

		// 通过Window继承
		void OnUpdate() override;  // 缓冲区，轮询输入事件等等
		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }
		// WindowAttribute
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
		inline void* GetNativeWindow() const {
			// 返回void类型，是未来我们可能会把GLFW换掉
			return m_Window;
		}
	};
}


