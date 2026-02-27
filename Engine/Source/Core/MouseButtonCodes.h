#pragma once

// 来自GLFW，并把前缀替换为ENGINE作为引擎内部使用的KEY_CODE
// 为什么要用自己的，是因为DX之类的用的Code和这些是不一样的，GLFW对DX系列API支持的不是很好，基本得用Win32
// 考虑到扩展性（以后可以比如当平台是windows时，定义为一些值用win32，为另一些值时用glfw）
#define ENGINE_MOUSE_BUTTON_1         0
#define ENGINE_MOUSE_BUTTON_2         1
#define ENGINE_MOUSE_BUTTON_3         2
#define ENGINE_MOUSE_BUTTON_4         3
#define ENGINE_MOUSE_BUTTON_5         4
#define ENGINE_MOUSE_BUTTON_6         5
#define ENGINE_MOUSE_BUTTON_7         6
#define ENGINE_MOUSE_BUTTON_8         7
#define ENGINE_MOUSE_BUTTON_LAST      ENGINE_MOUSE_BUTTON_8
#define ENGINE_MOUSE_BUTTON_LEFT      ENGINE_MOUSE_BUTTON_1
#define ENGINE_MOUSE_BUTTON_RIGHT     ENGINE_MOUSE_BUTTON_2
#define ENGINE_MOUSE_BUTTON_MIDDLE    ENGINE_MOUSE_BUTTON_3