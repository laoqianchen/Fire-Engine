#pragma once

#include "Core/Renderer/RShader.h"

// 之后会删掉，这是为了通过编译的，因为这个文件可能被sandbox包含，包含的话我们没办法inclue "glad/glad.h"
// glad.h中写的就是这个东西
typedef unsigned int GLenum;

namespace Engine {
    class ROpenGLShader : public RShader
    {
    private:
        uint32_t m_RendererID;
        std::string m_Name;
    private:
        std::string ReadFile(const std::string& filePath);
        std::unordered_map<GLenum, std::string> ParseShaderSources(const std::string& shaderSource);
        void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);  // 编译着色器
    public:
        ROpenGLShader(const std::string& filePath);
        ROpenGLShader(const std::string& name, const std::string& filePath);
        ROpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
        virtual ~ROpenGLShader();

        // 通过 RShader 继承
        void Bind() const override;
        void UnBind() const override;
        const std::string& GetName() const override { return m_Name; }
        void UploadUniformInt(const std::string& name, int value) override;
        void UploadUniformFloat(const std::string& name, float value) override;
        void UploadUniformFloat2(const std::string& name, const glm::vec2& values) override;
        void UploadUniformFloat3(const std::string& name, const glm::vec3& values) override;
        void UploadUniformFloat4(const std::string& name, const glm::vec4& values) override;
        void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) override;
        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;
    };
}


