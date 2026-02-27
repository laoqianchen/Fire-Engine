#pragma once

// 通用头文件
#include <iostream>
#include <utility>
#include <algorithm>
#include <functional>  // 包含了std::function通用可调用对象封装...

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

// 到处都需要能打Log
#include "Core/Log.h"

//// windows特定需要的头文件
//#ifdef ENGINE_PLATFORM_WINDOWS 
//	#include <Windows.h>
//#endif