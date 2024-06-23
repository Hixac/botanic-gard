#include <mark.hpp>

#include <window.hpp>
#include <marble.hpp>

#include <string>

namespace MyGui {
	
	Mark::Mark(std::string label, ImVec2 pos)
		: m_label(label), m_oldres(Window::Window::GetVec()), m_pos(pos), m_isHovered(false),
		  m_pbriefcase(new BriefCase(label.c_str(), {0, 0}, {0, 0}))
	{ }
	
    void Mark::Update()
	{
		ImGui::SetCursorPos({ m_pos.x, m_pos.y});
		
		if (ImGui::Button(m_label.c_str())) {
		    m_isHovered = true;

		    m_pbriefcase->Activate();
			return;
			
		} else if (ImGui::IsItemHovered()) {
			m_isHovered = true;
			return;
		}
	    m_isHovered = false;
		return;
	}

	void Mark::UpdateFun()
	{
	    m_pbriefcase->Update();
	}
	
}
