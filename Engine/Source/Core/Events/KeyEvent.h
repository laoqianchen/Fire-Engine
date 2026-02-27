#pragma once

#include "Event.h"
#include <string>
#include <sstream>

namespace Engine {
	// 按键事件基类
	class ENGINE_API KeyEvent : public Event {
	protected:
		int m_KeyCode;
		// 没有其他类可以构造他，除了他的派生类
		KeyEvent(int keyCode) : m_KeyCode(keyCode) {}
	public:
		inline int GetKeyCode() const { return m_KeyCode; }
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	};

	// 按键按下事件类型
	class ENGINE_API KeyPressedEvent : public KeyEvent {
	private:
		int m_RepeatCount;  // 重复计数（在按下按键之后，会先执行一次Press，然后会执行一连串重复的Press，可以按下按键尝试一下aaaaaaaaaaaaaaaaa）
	public:
		KeyPressedEvent(int keyCode, int repeatCount) : KeyEvent(keyCode), m_RepeatCount(repeatCount){}
		inline int GetRepeatCount() const { return m_RepeatCount; }
		std::string ToString() const override {
			std::stringstream ss;
			ss << "按键按下事件：" << m_KeyCode << "（" << m_RepeatCount << "重复）";
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyPressed)
	};

	// 按键松开事件类型
	class ENGINE_API KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int keyCode) : KeyEvent(keyCode) {}
		std::string ToString() const override {
			std::stringstream ss;
			ss << "按键释放事件：" << m_KeyCode;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyReleased);
	};

	// 按键键入事件类型
	class ENGINE_API KeyTypedEvent : public KeyEvent {
	public:
		KeyTypedEvent(int keyCode) : KeyEvent(keyCode) {}
		std::string ToString() const override {
			std::stringstream ss;
			ss << "按键键入事件：" << m_KeyCode;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyTyped)
	};
}