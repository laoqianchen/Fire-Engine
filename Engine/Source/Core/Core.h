#pragma once

// 定义一些常用的宏等等

// 当目标文件是 DLL 时，凡是希望被 DLL 外部使用的符号，都必须“导出”
#ifdef ENGINE_PLATFORM_WINDOWS
	#ifdef ENGINE_BUILD_DLL 
		#define ENGINE_API __declspec(dllexport)
	#else
		#define ENGINE_API __declspec(dllimport)
	#endif
#else
	#error Engine only support windows!
#endif

#define BIT(x) (1 << x)

#ifdef  ENGINE_DEBUG
	#define	ENABLE_ASSERT	
#endif 

#ifdef ENABLE_ASSERT 
	#define ENGINE_ASSERT(x, ...) {if(!(x)){ENGINE_ERROR("静态断言: {}", __VA_ARGS__); __debugbreak();}}
	#define USER_ASSERT(x, ...) {if(!(x)){USER_ERROR("静态断言: {}", __VA_ARGS__); __debugbreak();}}
#else
	#define ENGINE_ASSERT(x, ...)
	#define USER_ASSERT(x, ...)
#endif

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

#include <memory>

// 自定义的智能指针
// （之后如果有需要的话，会在这里扩展成一些模板类，而非只是简单的命名替换）
// 比如我们可以对智能指针扩展额外的调试日志功能...
namespace Engine {
	template<typename T>
	using TUniquePtr = std::unique_ptr<T>;

	template<typename T>
	using TSharedPtr = std::shared_ptr<T>;

	template<typename T>
	using TWeakPtr = std::weak_ptr<T>;
}