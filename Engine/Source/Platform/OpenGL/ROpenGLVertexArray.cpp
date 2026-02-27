
#include "enginepch.h"
#include "ROpenGLVertexArray.h"
#include "glad/glad.h"

namespace Engine {

	GLuint ShaderDataType2OpenGLBaseType(EShaderDataType type)
	{
		switch (type)
		{
		case EShaderDataType::Float:
		case EShaderDataType::Float2:
		case EShaderDataType::Float3:
		case EShaderDataType::Float4:
		case EShaderDataType::Mat3:
		case EShaderDataType::Mat4:
			return GL_FLOAT;

		case EShaderDataType::Int:
		case EShaderDataType::Int2:
		case EShaderDataType::Int3:
		case EShaderDataType::Int4:
			return GL_INT;

		case EShaderDataType::Bool:
			return GL_BOOL;

		case EShaderDataType::None:
		default:
			// EngineAssert(false, "Unknown ShaderDataType!");
			return 0;
		}
	}

	ROpenGLVertexArray::ROpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}
	ROpenGLVertexArray::~ROpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}
	void ROpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}
	void ROpenGLVertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}
	void ROpenGLVertexArray::AddVertexBuffer(const TSharedPtr<RVertexBuffer>& vertexBuffer)
	{
		glBindVertexArray(m_RendererID);  // 确保顶点数组已经绑定
		vertexBuffer->Bind();
		ENGINE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "VertexBuffer has no layout! ");
		
		int index = 0;
		for (const auto& element : vertexBuffer->GetLayout()) {
			glEnableVertexAttribArray(index);  // layout=0的东西
			glVertexAttribPointer(
				index,
				element.GetScalarCount(),
				ShaderDataType2OpenGLBaseType(element.Type),
				element.bIsNormalized ? GL_TRUE : GL_FALSE,
				vertexBuffer->GetLayout().GetStride(),
				(const void*)element.Offset
			);  // 最后一个空指针指的是偏移量，一个顶点结束后到下一个顶点的偏移
			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}
	void ROpenGLVertexArray::SetIndexBuffer(const TSharedPtr<RIndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);  // 确保顶点数组已经绑定
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}
}
