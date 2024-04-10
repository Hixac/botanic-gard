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

		inline void SetSize(const ImVec2 size) { if (size.x > 0 && size.y > 0) m_size = size; }
		inline void SetPos(const ImVec2 pos)   { m_pos = pos; }
		
	private:
		std::function<void()> m_fn;
		
		const char* m_label;
		
		ImVec2 m_pos;
		ImVec2 m_size;
		
		ImGuiWindowFlags m_flags;
		
	};
	
}
