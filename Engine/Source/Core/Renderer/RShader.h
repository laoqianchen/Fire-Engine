#pragma once

#include "Core/Core.h"
// 暂时用的glm数学库，后续如果有了自己的数学库会换（尤其支持多种渲染API之后）
#include <glm/glm.hpp>

namespace Engine {
	class ENGINE_API RShader
	{
	public:
		virtual ~RShader() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual const std::string& GetName() const = 0;
		virtual void UploadUniformInt(const std::string& name, int value) = 0;
		virtual void UploadUniformFloat(const std::string& name, float value) = 0;
		virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& values) = 0;
		virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& values) = 0;
		virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& values) = 0;
		virtual void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) = 0;
		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;

		static RShader* Create(const std::string& filePath);
		static RShader* Create(const std::string& name, const std::string& filePath);
		// 这种直接从字符串生成的着色器需要手动指定一个名字，用于索引，而通过filePath来获取着色器的方式，名字即为着色器文件名
		static RShader* Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
	};

	class ENGINE_API RShaderLibrary {
	private:
		static RShaderLibrary* s_Instance;
		std::unordered_map<std::string, TSharedPtr<RShader>> m_Shaders;
	public:
		static void Create() { if (!s_Instance) s_Instance = new RShaderLibrary(); }
		static RShaderLibrary* Get() { return s_Instance; }
		bool IsShaderExist(const std::string& name);
		void AddShader(RShader* shader);
		void AddShaderFromFile(const std::string& filePath);
		TSharedPtr<RShader> GetShader(const std::string& name);
	};
}


