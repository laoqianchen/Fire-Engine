//
//#include <Engine.h>
//#include "imgui.h"
//#include "glm/gtc/matrix_transform.hpp"
//#include "glm/gtc/type_ptr.hpp"
//#include "Platform/OpenGL/ROpenGLShader.h"
//
//class ExampleLayer : public Engine::Layer {
//private:
//	// 纹理
//	Engine::TSharedPtr<Engine::RTexture> m_WoodTexture;
//	Engine::TSharedPtr<Engine::RTexture> m_MetalTexture;
//	Engine::TSharedPtr<Engine::RTexture> m_WaterTexture;
//	Engine::TSharedPtr<Engine::RTexture> m_StoneTexture;
//	Engine::TSharedPtr<Engine::RTexture> m_PaperTexture;
//	// 顶点数组
//	Engine::TSharedPtr<Engine::RVertexArray> m_VertexArray;
//	// 相机
//	Engine::TSharedPtr<Engine::RCamera> m_Camera;
//	float m_CameraSpeed = 1.f;  // 相机移动速度
//	// 定向光（太阳）
//	Engine::TSharedPtr<Engine::RDirectionalLight> m_DirectionalLight;
//	// 定向光参数
//	float m_DirectionalLightIntensity = 1.f;
//	glm::vec3 m_DirectionalLightColor = glm::vec3(1.f);
//	glm::vec3 m_DirectionalLightRotation = glm::vec3(-45.f, 45.f, 0.f);
//public:
//	ExampleLayer() : Layer("Example") {
//		m_VertexArray = Engine::TSharedPtr<Engine::RVertexArray>(Engine::RVertexArray::Create());
//		// 如果没有提供投影矩阵，那么OpenGL就直接用的默认的裁剪空间，也就是从-1到1的小立方体
//		// 每个顶点：x, y, z, u, v
//		float vertices[] = {
//			// Front face (Z+)
//			-0.5f, -0.5f,  0.5f,   0.f, 0.f, 1.f,   0.0f, 0.0f, // 0
//			 0.5f, -0.5f,  0.5f,   0.f, 0.f, 1.f,   1.0f, 0.0f, // 1
//			 0.5f,  0.5f,  0.5f,   0.f, 0.f, 1.f,   1.0f, 1.0f, // 2
//			-0.5f,  0.5f,  0.5f,   0.f, 0.f, 1.f,   0.0f, 1.0f, // 3
//
//			// Back face (Z-)
//			-0.5f, -0.5f, -0.5f,   0.f, 0.f, -1.f,  1.0f, 0.0f, // 4
//			-0.5f,  0.5f, -0.5f,   0.f, 0.f, -1.f,  1.0f, 1.0f, // 5
//			 0.5f,  0.5f, -0.5f,   0.f, 0.f, -1.f,  0.0f, 1.0f, // 6
//			 0.5f, -0.5f, -0.5f,   0.f, 0.f, -1.f,  0.0f, 0.0f, // 7
//
//			 // Left face (X-)
//			 -0.5f, -0.5f, -0.5f,  -1.f, 0.f, 0.f,   0.0f, 0.0f, // 8
//			 -0.5f, -0.5f,  0.5f,  -1.f, 0.f, 0.f,   1.0f, 0.0f, // 9
//			 -0.5f,  0.5f,  0.5f,  -1.f, 0.f, 0.f,   1.0f, 1.0f, //10
//			 -0.5f,  0.5f, -0.5f,  -1.f, 0.f, 0.f,   0.0f, 1.0f, //11
//
//			 // Right face (X+)
//			  0.5f, -0.5f, -0.5f,   1.f, 0.f, 0.f,   1.0f, 0.0f, //12
//			  0.5f,  0.5f, -0.5f,   1.f, 0.f, 0.f,   1.0f, 1.0f, //13
//			  0.5f,  0.5f,  0.5f,   1.f, 0.f, 0.f,   0.0f, 1.0f, //14
//			  0.5f, -0.5f,  0.5f,   1.f, 0.f, 0.f,   0.0f, 0.0f, //15
//
//			  // Top face (Y+)
//			  -0.5f,  0.5f, -0.5f,   0.f, 1.f, 0.f,   0.0f, 0.0f, //16
//			  -0.5f,  0.5f,  0.5f,   0.f, 1.f, 0.f,   0.0f, 1.0f, //17
//			   0.5f,  0.5f,  0.5f,   0.f, 1.f, 0.f,   1.0f, 1.0f, //18
//			   0.5f,  0.5f, -0.5f,   0.f, 1.f, 0.f,   1.0f, 0.0f, //19
//
//			   // Bottom face (Y-)
//			   -0.5f, -0.5f, -0.5f,   0.f, -1.f, 0.f,  1.0f, 1.0f, //20
//				0.5f, -0.5f, -0.5f,   0.f, -1.f, 0.f,  0.0f, 1.0f, //21
//				0.5f, -0.5f,  0.5f,   0.f, -1.f, 0.f,  0.0f, 0.0f, //22
//			   -0.5f, -0.5f,  0.5f,   0.f, -1.f, 0.f,  1.0f, 0.0f  //23
//		};
//
//		auto vertexBuffer = Engine::TSharedPtr<Engine::RVertexBuffer>(Engine::RVertexBuffer::Create(vertices, sizeof(vertices)));
//
//		Engine::RBufferLayout layout = {
//			{Engine::EShaderDataType::Float3, "a_Position"},
//			{Engine::EShaderDataType::Float3, "a_Normal"},
//			{Engine::EShaderDataType::Float2, "a_TexCoord"}
//		};
//		vertexBuffer->SetLayout(layout);
//		m_VertexArray->AddVertexBuffer(vertexBuffer);
//
//		// 索引缓冲区
//		uint32_t indices[] = {
//			0, 1, 2,  2, 3, 0,       // Front
//			4, 5, 6,  6, 7, 4,       // Back
//			8, 9,10, 10,11, 8,       // Left
//		   12,13,14, 14,15,12,       // Right
//		   16,17,18, 18,19,16,       // Top
//		   20,21,22, 22,23,20        // Bottom
//		};
//		auto indexBuffer = Engine::TSharedPtr<Engine::RIndexBuffer>(Engine::RIndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
//		m_VertexArray->SetIndexBuffer(indexBuffer);
//
//		// 临时的纯色着色器
//		Engine::RShaderLibrary::Get()->AddShaderFromFile("Assets/Shaders/PureColor.glsl");
//		// 临时的纹理着色器
//		Engine::RShaderLibrary::Get()->AddShaderFromFile("Assets/Shaders/Texture.glsl");
//		// 临时的光照着色器
//		Engine::RShaderLibrary::Get()->AddShaderFromFile("Assets/Shaders/Lambert.glsl");
//
//		m_WoodTexture = Engine::TSharedPtr<Engine::RTexture>(Engine::RTexture2D::Create("Assets/Textures/Texturelabs_Wood_289S.jpg"));
//		m_MetalTexture = Engine::TSharedPtr<Engine::RTexture>(Engine::RTexture2D::Create("Assets/Textures/Texturelabs_Metal_282S.jpg"));
//		m_WaterTexture = Engine::TSharedPtr<Engine::RTexture>(Engine::RTexture2D::Create("Assets/Textures/Texturelabs_Water_142S.jpg"));
//		m_StoneTexture = Engine::TSharedPtr<Engine::RTexture>(Engine::RTexture2D::Create("Assets/Textures/Texturelabs_Stone_138S.jpg"));
//		m_PaperTexture = Engine::TSharedPtr<Engine::RTexture>(Engine::RTexture2D::Create("Assets/Textures/Texturelabs_Paper_361S.jpg"));
//
//		// m_Camera = std::make_shared<ROrthographicCamera>(-1.f, 1.f, -1.f, 1.f);
//		m_Camera = std::make_shared<Engine::RPerspectiveCamera>(90.f, 1280.f / 720.f, 0.1f, 100.f);
//		m_Camera->SetLocation(glm::vec3(0.f, 0.f, 1.f));
//		m_Camera->SetRotation(glm::vec3(0.f, 0.f, 0.f));
//		Engine::CameraController::Get()->SetCamera(m_Camera);  // 将这个相机交由相机控制器做默认的控制
//
//		// m_DirecitonalLight
//		m_DirectionalLight = std::make_shared<Engine::RDirectionalLight>();
//		m_DirectionalLight->SetIntensity(1.f);
//		m_DirectionalLight->SetRotation(glm::vec3(0.f, 0.f, 0.f));
//	}
//
//	void OnUpdate(float deltaTime) override {
//		// USER_INFO("{}", deltaTime);
//		// 清屏幕
//		Engine::RRenderer& renderer = Engine::RRenderer::Get();
//		renderer.SetClearColor({ 0.f, 0.f, 0.f, 1.f });
//		renderer.Clear();
//		// 渲染场景
//		m_DirectionalLight->SetIntensity(m_DirectionalLightIntensity);
//		m_DirectionalLight->SetColor(m_DirectionalLightColor);
//		m_DirectionalLight->SetRotation(m_DirectionalLightRotation);
//		renderer.BeginScene(m_Camera.get(), m_DirectionalLight.get());
//		// 绑定着色器，方便上传uniform
//		auto& shader = Engine::RShaderLibrary::Get()->GetShader("Lambert");
//		shader->Bind();
//		// 绘制5个物体
//		glm::mat4 transform = glm::mat4(1.f);
//		transform = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, 0.f));
//		renderer.Submit(m_VertexArray.get(), shader.get(), m_WoodTexture.get(), transform);
//		transform = glm::translate(glm::mat4(1.f), glm::vec3(2.f, 0.f, 0.f));
//		renderer.Submit(m_VertexArray.get(), shader.get(), m_MetalTexture.get(), transform);
//		transform = glm::translate(glm::mat4(1.f), glm::vec3(4.f, 0.f, 0.f));
//		renderer.Submit(m_VertexArray.get(), shader.get(), m_WaterTexture.get(), transform);
//		transform = glm::translate(glm::mat4(1.f), glm::vec3(6.f, 0.f, 0.f));
//		renderer.Submit(m_VertexArray.get(), shader.get(), m_StoneTexture.get(), transform);
//		transform = glm::translate(glm::mat4(1.f), glm::vec3(8.f, 0.f, 0.f));
//		renderer.Submit(m_VertexArray.get(), shader.get(), m_PaperTexture.get(), transform);
//		transform = glm::scale(glm::mat4(1.f), glm::vec3(50.f,1.f,50.f)) * glm::translate(glm::mat4(1.f), glm::vec3(0.f, -2.f, 0.f));
//		renderer.Submit(m_VertexArray.get(), shader.get(), m_WoodTexture.get(), transform);
//		renderer.EndScene();
//	}
//
//	void OnEvent(Engine::Event& e) override {
//	}
//
//	void OnImGuiRender() override {
//		ImGui::Begin("Settings");  // 开启一个ImGui窗口
//		// 光强度
//		ImGui::SliderFloat("DirectionalLightIntensity", &m_DirectionalLightIntensity, 0.0f, 10.0f);
//		// 光颜色
//		ImGui::ColorEdit3("DirectionalLightColor", glm::value_ptr(m_DirectionalLightColor));
//		// 定向光旋转（欧拉角，0~360）
//		ImGui::SliderFloat3("DirectionalLightRotation", glm::value_ptr(m_DirectionalLightRotation), 0.0f, 360.0f);
//		ImGui::End();
//	}
//};
//
//class SandBox : public Engine::Application {
//public:
//	SandBox() {
//		PushLayer(new ExampleLayer());
//	}
//};
//
//Engine::Application* Engine::CreateApplication() {
//	return new SandBox();
//}