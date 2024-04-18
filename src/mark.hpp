#pragma once

#include <imgui.h>

#include <functional>
#include <string>
#include <vector>

namespace MyGui {
	
	class Mark
	{
	public:
		Mark(std::string label, ImVec2 pos, std::function<void()> fn);

		void UpdateFun();
	    bool Update();

		inline bool IsHovered() { return m_isHovered; };
		
	private:
		bool m_isHovered;
		
		std::function<void()> m_fn;
		
		std::string m_label;
		ImVec2 m_pos;
	};

	class MarkContainer
	{
	public:
		MarkContainer() = default;

		void Add(ImVec2 pos, std::function<void()> fn);
		bool Any(Mark* mark = nullptr);

		inline size_t GetSize() { return m_marks.size(); }
		
		inline std::vector<Mark>& operator()() { return m_marks; }
		
	private:
		std::vector<Mark> m_marks;
	};
	
}
