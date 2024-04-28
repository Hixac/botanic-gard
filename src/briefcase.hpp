#pragma once

#include <frame.hpp>
#include <image_render.hpp>

#include <string>

namespace MyGui {

	class BriefCase : public AbstractFrame
	{
	public:
		BriefCase(const char* label, ImVec2 size, ImVec2 pos, ImGuiWindowFlags flags = 0);

	    void Update() override;
		inline void SetActive(bool active) { m_active = active; }
		inline bool IsActive() { return m_active; }
		
		std::string name;
		std::string description;
	    Image image;

	private:
		bool m_active;
		
	};
	
}
