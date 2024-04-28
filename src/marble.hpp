#pragma once

#include <mark.hpp>
#include <frame.hpp>

#include <vector>

#include <imgui.h>

namespace Utils {

	enum class WindowType { Frame, Briefcase };
	
	class Marble
	{		
	public:		
		inline static Marble& Get() { static Marble m; return m; }

		void DoPortionCalc(MyGui::Mark* mark);

		// This function have no point. Maybe delete it later. But it may be useful.
		inline void Add(MyGui::AbstractFrame* frame, WindowType type) { m_balls.push_back({frame, type}); }
		
	private:
		std::vector<std::pair<MyGui::AbstractFrame*, WindowType>> m_balls;
		
		Marble()  = default;
		~Marble() = default;
	};
	
}
