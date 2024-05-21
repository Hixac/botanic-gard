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

		void DoPortionCalc(MyGui::Mark* mark);

		// FILENAME POINTS TO PNG FILE;; for quite big files I can use async either threading
		void SaveInfo(const std::string& filename, const std::string& pngname, MyGui::MarkContainer& marks);
		MyGui::MarkContainer LoadInfo(const std::string& filename, std::string& out_pngname);
		
		inline void Add(MyGui::AbstractFrame* frame, WindowType type) { m_balls.push_back({frame, type}); }
		
	private:
		std::vector<std::pair<MyGui::AbstractFrame*, WindowType>> m_balls;
		
		Marble()  = default;
		~Marble() = default;
	};
	
}
