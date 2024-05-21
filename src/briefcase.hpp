#pragma once

#include <frame.hpp>
#include <image_render.hpp>

#include <vector>
#include <string>

namespace MyGui {

	struct Info
	{
		std::string name;
		std::string descr;
		bool isBig;
	};

	class BriefCase : public AbstractFrame
	{
	public:
		BriefCase(const char* label, ImVec2 size, ImVec2 pos, ImGuiWindowFlags flags = 0);

	    void Update() override;
		inline void SetActive(bool active) { m_active = active; }
		inline bool IsActive() { return m_active; }

		inline bool ToDestroy() { return m_destroy; }

		// incapsulation violation (ikr idgaf)
		std::string name;
		std::vector<Info> vec_info;
	    Image image;

	private:
		bool m_active;
		bool m_destroy;
		
	};
	
}
