#include <mark.hpp>

#include <window.hpp>
#include <marble.hpp>

#include <string>

namespace MyGui {
	
	Mark::Mark(std::string label, ImVec2 pos)
		: m_label(label), m_oldres(Window::Window::GetVec()), m_pos(pos), m_isHovered(false),
		  m_pbriefcase(new BriefCase("herro", {0, 0}, {0, 0}))
	{ }
	
    bool Mark::Update()
	{
		ImGui::SetCursorPos({ m_pos.x, m_pos.y});
		
		if (ImGui::Button(m_label.c_str())) {
		    m_isHovered = true;

			m_pbriefcase->SetActive(true);
			return true;
			
		} else if (ImGui::IsItemHovered()) {
			m_isHovered = true;

			m_pbriefcase->SetActive(false);
			return false;
		}

		m_pbriefcase->SetActive(false);
	    m_isHovered = false;
		return false;
	}

	void Mark::UpdateFun()
	{
	    m_pbriefcase->Update();
	}
	
}
