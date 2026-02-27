
#include "enginepch.h"
#include "ROpenGLBuffer.h"
#include <glad/glad.h>

namespace Engine {
	ROpenGLVertexBuffer::ROpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		// glCreateBuffers(1, &m_RendererID)相当于
		// glGenBuffers(1, &m_VertexBuffer);
		// 第二个参数size要传入的就是有多少个字节
		// GL_STATIC_DRAW这种用途意味着我们不会频繁更新这个BUFFER
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	ROpenGLVertexBuffer::~ROpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void ROpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void ROpenGLVertexBuffer::UnBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	ROpenGLIndexBuffer::ROpenGLIndexBuffer(uint32_t* indices, uint32_t count) : m_Count(count)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t)*count, indices, GL_STATIC_DRAW);
	}

	ROpenGLIndexBuffer::~ROpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void ROpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void ROpenGLIndexBuffer::UnBind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}
