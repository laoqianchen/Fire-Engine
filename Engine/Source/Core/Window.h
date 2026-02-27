#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Engine {
	struct FWindowProps {
		std::string Title;
		unsigned int Width;
		unsigned int Height;
		
		FWindowProps(const std::string& title = "TriggerEngine",
			unsigned int width = 1280,
			unsigned int height = 720) : Title(title), Width(width), Height(height) {}
	};

	class ENGINE_API Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;  // 事件回调函数
		virtual ~Window() {}
		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// windowAttributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;
		virtual void* GetNativeWindow() const = 0;  // 返回void类型，是未来我们可能会把GLFW换掉
		
		static Window* Create(const FWindowProps& props = FWindowProps());  // 每个平台上都会做不同的实现
	};
}