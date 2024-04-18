#include <mark.hpp>

#include <window.hpp>

#include <string>

namespace MyGui {
	
	Mark::Mark(std::string label, ImVec2 pos, std::function<void()> fn)
		: m_label(label), m_pos(pos), m_fn(fn), m_isHovered(false)
	{ }

    bool Mark::Update()
	{
		ImGui::SetCursorPos(m_pos);
		if (ImGui::Button(m_label.c_str())) {
		    m_isHovered = true;
			
			return true;
			
		} else if (ImGui::IsItemHovered()) {
			m_isHovered = true;

			return false;
		}
	    
	    m_isHovered = false;
		return false;
	}

	void Mark::UpdateFun()
	{
		m_fn();
	}

    void MarkContainer::Add(ImVec2 pos, std::function<void()> fn)
	{
		Mark mark(std::to_string(m_marks.size() + 1), pos, fn);
		m_marks.push_back(mark);
	}

	bool MarkContainer::Any(Mark* mark)
	{
		for (auto& m : m_marks) {
			if (m.IsHovered()) {
				mark = &m;
				return true;
			}
		}

		return false;
	}
}
