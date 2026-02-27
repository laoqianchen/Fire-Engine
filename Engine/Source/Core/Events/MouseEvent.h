#pragma once

#include "Event.h"
#include <string>
#include <sstream>

namespace Engine {
	// 鼠标移动事件
	class ENGINE_API MouseMovedEvent : public Event {
	private:
		double m_MouseX;
		double m_MouseY;
	public:
		MouseMovedEvent(double x, double y) : m_MouseX(x), m_MouseY(y) {}
		inline double GetX() const { return m_MouseX; }
		inline double GetY() const { return m_MouseY; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "鼠标移动事件：" << m_MouseX << "," << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};

	// 鼠标滚动事件
	class ENGINE_API MouseScrolledEvent : public Event {
	private:
		// 有些鼠标可以横向滚动（所以包含了X与Y两个偏移量）
		double m_XOffset;
		double m_YOffset;
	public:
		MouseScrolledEvent(double xOffset, double yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {}
		inline double GetXOffset() const { return m_XOffset; }
		inline double GetYOffset() const { return m_YOffset; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "鼠标滚动事件：" << m_XOffset << "，" << m_YOffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};

	// 鼠标按键事件基类（无法在外部构造，只能由他的子类进行构造）
	class ENGINE_API MouseButtonEvent : public Event {
	protected:
		int m_Button;
		MouseButtonEvent(int button) : m_Button(button) {}
	public:
		inline int GetMouseButton() const { return m_Button; }
		
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryMouseButton | EventCategoryInput)
	};

	// 鼠标按键按下事件
	class ENGINE_API MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}
		std::string ToString() const override {
			std::stringstream ss;
			ss << "鼠标按下事件：" << m_Button;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	// 鼠标按键松开事件
	class ENGINE_API MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}
		std::string ToString() const override {
			std::stringstream ss;
			ss << "鼠标松开事件：" << m_Button;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}