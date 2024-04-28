#pragma once

#include <mark.hpp>
#include <imgui.h>

#include <vector>

namespace MyGui {
	
	class MarkContainer
	{	
	public:
		MarkContainer() = default;

		void Add(ImVec2 pos);
		bool Any(Mark* mark = nullptr);
		
		inline void Clear() { m_marks.clear(); }
		
		inline size_t GetSize() { return m_marks.size(); }
		
		inline std::vector<Mark>& operator()() { return m_marks; }
		
	private:
		std::vector<Mark> m_marks;
    };

}
