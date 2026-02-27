
#include "enginepch.h"
#include "ROpenGLTexture.h"

#include <stb_image.h>
#include <glad/glad.h>

namespace Engine {
	ROpenGLTexture2D::ROpenGLTexture2D(const std::string& path) : m_Path(path)
	{
		// 因为stb库导入的图像和opengl的纹理正好上下是颠倒的，所以需要导入时做一次上下翻转操作
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &m_Width, &m_Height, &m_Channels, 0);
		ENGINE_ASSERT(data, "Failed to load image!");
		// 根据Channel数量，确定内部存储格式以及数据格式
		GLenum internalFormat = 0, dataFormat = 0;
		if (m_Channels == 4) {
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (m_Channels == 3) {
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}
		ENGINE_ASSERT(internalFormat && dataFormat, "Image format is not supported!");
		// 将纹理图片的数据，上传到纹理缓冲区
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);
		// 纹理不够小，不够大时均使用线性插值/最近邻
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		// 上传纹理
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);
		// 一旦上传到gpu，cpu上的纹理数据就不需要了
		stbi_image_free(data);
	}
	ROpenGLTexture2D::~ROpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}
	void ROpenGLTexture2D::Bind(unsigned int slot) const
	{
		// 绑定到0号纹理插槽
		glBindTextureUnit(slot, m_RendererID);
	}
}

