#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"

// 这是一个引擎日志单例类，其具体的实现暂时是基于第三方库-spdlog

namespace Engine {
	class ENGINE_API Log
	{
	public:
		static void Init();
		inline static TSharedPtr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static TSharedPtr<spdlog::logger>& GetUserLogger() { return s_UserLogger; }
	private:
		// 两个日志记录器，一个用于引擎（Core），一个用于用户（User）
		static TSharedPtr<spdlog::logger> s_CoreLogger;
		static TSharedPtr<spdlog::logger> s_UserLogger;
	};
}

// 定义一些宏，以便能方便地使用
// 引擎核心日志宏
#define ENGINE_TRACE(...) ::Engine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ENGINE_INFO(...) ::Engine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ENGINE_WARN(...) ::Engine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ENGINE_ERROR(...) ::Engine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ENGINE_FATAL(...) ::Engine::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// 用户日志宏
#define USER_TRACE(...) ::Engine::Log::GetUserLogger()->trace(__VA_ARGS__)
#define USER_INFO(...) ::Engine::Log::GetUserLogger()->info(__VA_ARGS__)
#define USER_WARN(...) ::Engine::Log::GetUserLogger()->warn(__VA_ARGS__)
#define USER_ERROR(...) ::Engine::Log::GetUserLogger()->error(__VA_ARGS__)
#define USER_FATAL(...) ::Engine::Log::GetUserLogger()->fatal(__VA_ARGS__)

