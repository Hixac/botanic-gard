#pragma once

#include <mark.hpp>
#include <frame.hpp>
#include <markcontainer.hpp>

#include <vector>

#include <imgui.h>

namespace Utils {

	enum class WindowType { Frame, Briefcase };
	
	class Marble
	{		
	public:		
		inline static Marble& Get() { static Marble m; return m; }

		void DoPortionCalc();

		// FILENAME POINTS TO PNG FILE;; for quite big files I can use async either threading
		void SaveInfo(const std::string& filename, MyGui::Image& image, MyGui::MarkContainer& marks);
		MyGui::MarkContainer LoadInfo(const std::string& filename, MyGui::Image& image);
		
		inline void Add(MyGui::AbstractFrame* frame, WindowType type) { m_balls.push_back({frame, type}); }

		inline bool IsActivated() { return m_is_acivated_briefcase; }
		inline float BriefcaseSize() { return m_briefcase_size_x; }
		
	private:
		std::vector<std::pair<MyGui::AbstractFrame*, WindowType>> m_balls;

		float m_briefcase_size_x;
		bool m_is_acivated_briefcase = false;
		
		Marble()  = default;
		~Marble() = default;
	};
	
}
