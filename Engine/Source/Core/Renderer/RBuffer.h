#pragma once

#include "Core/Core.h"

namespace Engine {
	
	// 这里这个枚举类型的命名方式和HLSL差不多
	// 这个枚举主要是方便确定布局的
	enum class EShaderDataType : uint8_t {
		None,
		Float, Float2, Float3, Float4,
		Int, Int2, Int3, Int4,
		Mat3, Mat4,
		Bool
	};

	static uint32_t GetShaderDataTypeSize(EShaderDataType type){
		switch (type)
		{
		case EShaderDataType::None:    return 0;

		case EShaderDataType::Float:   return 4;
		case EShaderDataType::Float2:  return 4 * 2;
		case EShaderDataType::Float3:  return 4 * 3;
		case EShaderDataType::Float4:  return 4 * 4;

		case EShaderDataType::Int:     return 4;
		case EShaderDataType::Int2:    return 4 * 2;
		case EShaderDataType::Int3:    return 4 * 3;
		case EShaderDataType::Int4:    return 4 * 4;

		case EShaderDataType::Mat3:    return 4 * 3 * 3; // 3 vec3
		case EShaderDataType::Mat4:    return 4 * 4 * 4; // 4 vec4

		case EShaderDataType::Bool:    return 1; // 逻辑上 1 byte，OpenGL 会扩展

		default:
			// EngineAssert(false, "Unknown ShaderDataType!");
			return 0;
		}
	}

	struct FBufferElement {
		std::string Name;
		EShaderDataType Type = EShaderDataType::None;
		uint32_t Offset = 0;
		uint32_t Size = 0;
		bool bIsNormalized = false;
		FBufferElement() {}
		FBufferElement(EShaderDataType type, const std::string& name, bool normalized = false) : Type(type), Name(name), bIsNormalized(normalized), Size(GetShaderDataTypeSize(type)) {}
		
		uint32_t GetScalarCount() const
		{
			switch (Type)
			{
			case EShaderDataType::None:   return 0;

			case EShaderDataType::Float:  return 1;
			case EShaderDataType::Float2: return 2;
			case EShaderDataType::Float3: return 3;
			case EShaderDataType::Float4: return 4;

			case EShaderDataType::Int:    return 1;
			case EShaderDataType::Int2:   return 2;
			case EShaderDataType::Int3:   return 3;
			case EShaderDataType::Int4:   return 4;

			case EShaderDataType::Bool:   return 1;

			case EShaderDataType::Mat3:   return 3;  // Mat3的ScalerCount（要传入glVertexAttribPointer的size是3，表示3个vec3）
			case EShaderDataType::Mat4:   return 4;  // Mat4的ScalerCount（要传入glVertexAttribPointer的size是4，表示4个vec4）

			default:
				// EngineAssert(false, "Unknown ShaderDataType!");
				return 0;
			}
		}
	};

	class ENGINE_API RBufferLayout {
	private:
		std::vector<FBufferElement> m_Elements;
		uint32_t m_Stride = 0;  // 最终这个布局中元素的步幅（也就是最终一个元素有多少字节）
	private:
		void CalcOffsetsAndStride() {
			uint32_t offset = 0;
			for (FBufferElement& element : m_Elements) {
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
	public:
		RBufferLayout() {}
		// 这样就可以直接用RBufferLayer layout = {}来直接初始化了，传vector的话需要三层{}
		RBufferLayout(const std::initializer_list<FBufferElement>& elements) : m_Elements(elements){
			// 初始化结束后，才能得到每一个元素的偏移与总体的Stride
			CalcOffsetsAndStride();
		}
		inline std::vector<FBufferElement> GetElements() const { return m_Elements; }
		inline uint32_t GetStride() const { return m_Stride; }
	
		// 方便直接实现for( : RBufferLayout)的遍历
		std::vector<FBufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<FBufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<FBufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<FBufferElement>::const_iterator end() const { return m_Elements.end(); }
	};

	// 这些都是纯虚接口

	class ENGINE_API RVertexBuffer
	{
	public:
		virtual ~RVertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual const RBufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const RBufferLayout& layout) = 0;

		// 因为这是一个抽象类，构造函数是没办法用的，无法构造抽象类型，但是如果用静态函数，子类做不同实现就可以
		// 相当于是工厂模式
		static RVertexBuffer* Create(float* vertices, uint32_t size);
	};

	class ENGINE_API RIndexBuffer
	{
	public:
		virtual ~RIndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual uint32_t GetCount() const = 0;

		// 因为这是一个抽象类，构造函数是没办法用的，无法构造抽象类型，但是如果用静态函数，子类做不同实现就可以
		// 相当于是工厂模式
		static RIndexBuffer* Create(uint32_t* indices, uint32_t size);
	};
}

