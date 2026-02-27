#pragma once

#include "Event.h"
#include <string>
#include <sstream>

namespace Engine {
	// 窗口调整大小事件
	class ENGINE_API WindowResizeEvent : public Event {
	private:
		unsigned int m_Width;
		unsigned int m_Height;
	public:
		WindowResizeEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) {}

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "窗口大小改变事件：" << m_Width << "，" << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	// 窗口关闭事件
	class ENGINE_API WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() {}
		
		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	// AppTick事件
	class ENGINE_API AppTickEvent : public Event {
	public:
		AppTickEvent() {}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	// AppUpdate事件
	class ENGINE_API AppUpdateEvent : public Event {
	public:
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	// AppRender事件
	class ENGINE_API AppRenderEvent : public Event {
	public:
		AppRenderEvent(){}
		
		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}