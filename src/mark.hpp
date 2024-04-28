#pragma once

#include <briefcase.hpp>
#include <imgui.h>

#include <memory>
#include <string>

namespace MyGui {
	
	class Mark
	{
	public:
		Mark(std::string label, ImVec2 pos);

		void UpdateFun();
	    bool Update();

		inline bool IsHovered() { return m_isHovered; };
		inline MyGui::BriefCase& GetBriefCase() { return *m_pbriefcase; }
		
	private:
		
		std::string name;
		
		bool m_isHovered;
		
		std::unique_ptr<MyGui::BriefCase> m_pbriefcase;
		
		std::string m_label;
		ImVec2 m_pos;

		ImVec2 m_oldres;
	};
	
}
