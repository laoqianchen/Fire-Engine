#pragma once

// Engine.h在引擎项目的Core文件夹之外，
// 这个Engine.h是专门用于用户程序的，
// 用户程序会包含这个头文件（并且只需要包含引擎提供的这一个头文件），而Engine内部不会关心

#include "Core/Application.h"

// ============日志================
#include "Core/Log.h"
// ==================================

// ============层================
#include "Core/Layer.h"
#include "Core/ImGui/ImGuiLayer.h"
// ==================================

// ============输入================
#include "Core/Input.h"
#include "Core/KeyCodes.h"
#include "Core/MouseButtonCodes.h"
// ==================================

// ============事件================
#include "Core/Events/Event.h"
#include "Core/Events/KeyEvent.h"
#include "Core/Events/MouseEvent.h"
#include "Core/Events/ApplicationEvent.h"
// ==================================

// ============渲染器相关================
#include "Core/Renderer/RCamera.h"
#include "Core/CameraController.h"
#include "Core/Renderer/RLight.h"
#include "Core/Renderer/RBuffer.h"
#include "Core/Renderer/RShader.h"
#include "Core/Renderer/RTexture.h"
#include "Core/Renderer/RVertexArray.h"
#include "Core/Renderer/RRenderer.h"
// ==================================

// ============入口点================
#include "Core/EntryPoint.h"
// ==================================