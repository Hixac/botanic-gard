#pragma once

#include <functional>
#include <imgui.h>

namespace MyGui {

	class Frame
	{
	public:
		Frame(const char* label, ImVec2 size, ImVec2 pos, ImGuiWindowFlags flags = 0);

		inline void SetFunction(std::function<void()> fn) { m_fn = fn; }
		void Update();
		
	private:
		std::function<void()> m_fn;
		
		const char* m_label;
		
		ImVec2 m_pos;
		ImVec2 m_size;
		
		ImGuiWindowFlags m_flags;
		
	};
	
}
