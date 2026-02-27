
#include "enginepch.h"
#include "ROpenGLShader.h"

#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Engine {
	std::string ROpenGLShader::ReadFile(const std::string& filePath)
	{
		std::string res;
		std::ifstream in(filePath, std::ios::in | std::ios::binary);
		if (!in) {
			// 某几个着色器加载失败或许是可以接受的
			ENGINE_WARN("Fail to load shader file!'{}'", filePath);
			return res;
		}
		// 通过文件指针的位置，知晓文件大小
		// 将文件指针置于文件末尾
		in.seekg(0, std::ios::end);
		res.resize(in.tellg());
		// 将文件指针置于文件开头，从而传输数据
		in.seekg(0, std::ios::beg);
		in.read(&res[0], res.size());
		// 关闭数据流
		in.close();
		return res;
	}

	std::unordered_map<GLenum, std::string> ROpenGLShader::ParseShaderSources(const std::string& shaderSource)
	{
		std::unordered_map<GLenum, std::string> res;

		const char* typeToken = "#type";
		const size_t typeTokenLength = strlen(typeToken);

		size_t pos = shaderSource.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			// 当前 #type 行结尾
			size_t eol = shaderSource.find_first_of("\r\n", pos);
			ENGINE_ASSERT(eol != std::string::npos, "Shader syntax error: missing end of line after #type");

			// 解析 shader 类型字符串
			size_t begin = pos + typeTokenLength;
			// 跳过空格
			while (begin < eol && shaderSource[begin] == ' ')
				begin++;

			std::string type = shaderSource.substr(begin, eol - begin);

			// 类型校验 + 映射
			GLenum shaderType = 0;
			if (type == "vertexShader")
				shaderType = GL_VERTEX_SHADER;
			else if (type == "fragmentShader")
				shaderType = GL_FRAGMENT_SHADER;
			else
				ENGINE_ASSERT(false, "Invalid shader type: {0}", type);

			// Shader 源码开始位置（下一行）
			size_t nextLinePos = shaderSource.find_first_not_of("\r\n", eol);
			ENGINE_ASSERT(nextLinePos != std::string::npos, "Shader syntax error: missing shader code");

			// 查找下一个 #type
			pos = shaderSource.find(typeToken, nextLinePos);

			// 截取当前 shader 源码
			res[shaderType] =
				(pos == std::string::npos)
				? shaderSource.substr(nextLinePos)
				: shaderSource.substr(nextLinePos, pos - nextLinePos);
		}
		return res;
	}

	void ROpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		// 所有成功编译的着色器的ID
		std::vector<GLuint> shaderIDs;
		// 编译并attach着色器
		for (auto& kv : shaderSources) {
			GLenum shaderType = kv.first;
			const std::string& shaderSrc = kv.second;
			// ENGINE_INFO(shaderSrc);
			// 创建着色器
			GLuint shader = glCreateShader(shaderType);
			// 设置着色器文本
			const GLchar* sourceCstr = shaderSrc.c_str();
			glShaderSource(shader, 1, &sourceCstr, 0);
			// 编译着色器
			glCompileShader(shader);
			// 针对编译失败的处理
			GLint bIsCompiled = false;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &bIsCompiled);
			if (!bIsCompiled) {
				ENGINE_WARN("Failed to compile shader.");
				glDeleteShader(shader);
				continue;
			}else {
				// 只有着色器编译成功了才会放入
				shaderIDs.push_back(shader);
			}
		}
		// 创建一个新的着色器程序
		GLuint programID = glCreateProgram();
		// Attach所有shader
		for (auto& shaderID : shaderIDs) {
			glAttachShader(programID, shaderID);
		}
		// 链接
		glLinkProgram(programID);
		GLint bIsLinked = false;
		glGetProgramiv(programID, GL_LINK_STATUS, &bIsLinked);
		if (!bIsLinked) {
			ENGINE_WARN("Failed to link shader.");
			glDeleteProgram(programID);
		}else {
			// 链接成功，设置m_RendererID
			m_RendererID = programID;
		}
		// 总是链接完后解绑并删除所有shader（中间产物）
		for (auto& shaderID : shaderIDs) {
			glDetachShader(programID, shaderID);
			glDeleteShader(shaderID);
		}
	}
	
	ROpenGLShader::ROpenGLShader(const std::string& filePath)
	{
		std::string shaderSource = ReadFile(filePath);
		auto shaderSources = ParseShaderSources(shaderSource);
		Compile(shaderSources);
		// 设置着色器名称(文件名)
		size_t lastSlash = filePath.find_last_of("/\\");
		size_t lastDot = filePath.find_last_of(".");
		size_t begin = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		size_t end = lastDot == std::string::npos ? filePath.size() : lastDot;
		size_t count = end - begin;
		m_Name = filePath.substr(begin, count);
	}
	ROpenGLShader::ROpenGLShader(const std::string& name, const std::string& filePath)
	{
		std::string shaderSource = ReadFile(filePath);
		auto shaderSources = ParseShaderSources(shaderSource);
		Compile(shaderSources);
		// 设置着色器名称
		m_Name = name;
	}
	ROpenGLShader::ROpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
	{
		std::unordered_map<GLenum, std::string> shaderSources;
		shaderSources[GL_VERTEX_SHADER] = vertexSource;
		shaderSources[GL_FRAGMENT_SHADER] = fragmentSource;
		Compile(shaderSources);
		// 设置着色器名称
		m_Name = name;
	}
	ROpenGLShader::~ROpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}
	void ROpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}
	void ROpenGLShader::UnBind() const
	{
		glUseProgram(0);
	}
	void ROpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		GLuint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}
	void ROpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		GLuint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}
	void ROpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& values)
	{
		GLuint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, values.x, values.y);
	}
	void ROpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& values)
	{
		GLuint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, values.x, values.y, values.z);
	}
	void ROpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& values)
	{
		GLuint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, values.x, values.y, values.z, values.w);
	}
	void ROpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLuint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
	void ROpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}