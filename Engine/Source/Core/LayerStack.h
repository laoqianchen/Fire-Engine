#pragma once

#include "Core.h"

namespace Engine {

	class Layer;

	// 层栈本质上是对层vector的封装
	// 我们使用vector是因为我们还需要一个反向的迭代器用于反向传播事件
	// 没有用栈实现，因为我们需要把一些东西推入中间（例如覆层）
	// 各个层分为：{图层， 覆层}
	// PushLayer是推向层插入区的末尾
	// PushOverlay是推向后半部分
	// 当切换关卡等时，这个图层堆栈都会被重新构建

	class ENGINE_API LayerStack {
	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0;
	public:
		LayerStack();
		virtual ~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* layer);

		// 方便其他地方可以快速遍历(直接for( : ))
		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	};
}