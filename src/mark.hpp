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
	    void Update();

		inline bool ToDestroy() { return m_pbriefcase->ToDestroy(); }
		inline bool IsHovered() { return m_isHovered; };
		inline MyGui::BriefCase& GetBriefCase() { return *m_pbriefcase; }
		inline std::shared_ptr<MyGui::BriefCase>& GetBCPtr() { return m_pbriefcase; }

		inline std::string GetLabel() { return m_label; }
		inline ImVec2 GetPos() { return m_pos; }
		
		inline ImVec2 GetAbsPos(Image image) { return { (m_pos.x - image.GetCursorPos().x) / image.GetSize().x, (m_pos.y - image.GetCursorPos().y) / image.GetSize().y }; }
		
		inline void SetPos(ImVec2 pos) { m_pos = pos; }
		
	private:
		
		bool m_isHovered;
		
		std::shared_ptr<MyGui::BriefCase> m_pbriefcase;
		
		std::string m_label;
		ImVec2 m_pos;

		ImVec2 m_oldres;
	};
	
}
