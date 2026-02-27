#pragma once

#ifdef ENGINE_PLATFORM_WINDOWS
extern Engine::Application* Engine::CreateApplication();
int main(int argc, char* argv) {
	// 用于测试的代码
	Engine::Log::Init();
	ENGINE_ERROR("初始化日志! {}", 5);
	USER_WARN("初始化日志！{}", 5);

	Engine::Application* app = Engine::CreateApplication();
	app->Run();
	delete app;
}
#endif