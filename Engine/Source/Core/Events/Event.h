#pragma once

#include "Core/Core.h"
#include <string>

namespace Engine {
	// 事件现在是阻塞的，这意味着当事件发生时，程序会立刻停止运行，转而去处理这个事件
	// 非阻塞的那种：是从事件中获取信息，之后把信息扔进缓冲区或者队列，在延迟处理，甚至通过事件总线的方式传播出去

	// 各种事件类型，为每种事件分配了一个枚举值
	// 我们不想为了这么简单的事情而使用动态转换或者运行时类型信息
	// 为每种事件关联一个IntID就能处理了
	enum class EEventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	// 事件类型
	// 我们这么做的原因是因为我们可能会过滤掉一些事件：
	// 当应用程序接收到各种事件到某种事件类时，我只关心某些事件，比如我现在只关心键盘事件，
	// 那么MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled我们其实就没必要去检查了
	// 他这里枚举是用位域写的（也就是实现可以通过设置位的值来表示属于哪些类型），之后看看能否改一下，也就是实现了一个事件属于多个类别
	// 这里不能用enum class，否则没办法做int & EEventCategory的操作
	enum EEventCategory {
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) \
	static EEventType GetStaticType() {return EEventType::##type; }\
	virtual EEventType GetEventType() const override {return GetStaticType();}\
	virtual const char* GetName() const override {return #type;}

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return category;}

	// 事件类
	// 不同的事件子类会有不同的成员变量
	class ENGINE_API Event {
		friend class EventDispatcher;
	protected:
		bool m_bIsHandled = false;  // 是否已被处理（当我们开始将事件分发给不同层时，我们通常要决定要不要让事件继续传播下去，例如按钮被UI捕获，不希望传到游戏层中）
	public:
		virtual EEventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;  // 只用于调试，例如当窗口发生改变时，可以返回窗口的大小等等信息
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }  // 只用于调试
		inline bool IsHandled() { return m_bIsHandled; }
		inline bool IsInCategory(EEventCategory category) {
			return GetCategoryFlags() & category;
		}
	};

	// 事件分发器类
	// 一种能根据事件类型轻松分发事件的方法
	class EventDispatcher {
	private:
		Event& m_Event;
		// 模板别名EvenFn，
		// 一个“接收具体事件类型 T 引用，返回是否处理成功”的函数
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event) : m_Event(event) {}
		template<typename T>
		bool Dispatch(EventFn<T> func) {
			// 当前事件的真实类型是否等于模板参数T对应的事件类型
			if (m_Event.GetEventType() == T::GetStaticType()) {
				m_Event.m_bIsHandled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	};

	// 这个有BUG好像，按Cherno视频中的写法无法实现，而且也找不到解决方案
	// 会一直报错 C2079“_”使用未定义的 struct“fmt::v12::detail::type_is_unformattable_for<T, char>”
	// 没办法通过ENGINE_LOG(自定义类型)来打印Log日志
	// 所以暂时日志我们还是得用 ENGINE_TRACE(e.ToString()) 而不能 ENGINE_TRACE(e)
	//// 一个简单的输出流操作符
	//// 可以轻松地把事件转换成字符串，从而方便地记录Log
	//inline std::ostream& operator<<(std::ostream& os, const Event& e){
	//	return os << e.ToString();
	//}
}