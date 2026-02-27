#include "enginepch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Engine {
	TSharedPtr<spdlog::logger> Log::s_CoreLogger;
	TSharedPtr<spdlog::logger> Log::s_UserLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n:%v%$");
		s_CoreLogger = spdlog::stdout_color_mt("Engine");
		s_CoreLogger->set_level(spdlog::level::trace);
		s_UserLogger = spdlog::stdout_color_mt("User");
		s_UserLogger->set_level(spdlog::level::trace);
	}
}