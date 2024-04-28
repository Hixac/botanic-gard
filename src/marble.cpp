#include <marble.hpp>

#include <window.hpp>
#include <base.hpp>

#include <algorithm>

namespace Utils {
	
	void Marble::DoPortionCalc(MyGui::Mark* mark)
	{
		RAW_LOG_INFO(NC_TR_LOG("Frames pointer", 15) << NC_TR_LOG("Enum state", 1));
		for (int i = 0; i < m_balls.size(); ++i) {
			POINTER_LOG_INFO(m_balls[i].first, (int)m_balls[i].second, 5);
			if (!m_balls[i].first) m_balls.erase(m_balls.begin() + i);
		}

		static float briefcase_size = 500;
		if (mark == nullptr) { // restore all the shit that I made (im so sorry for this)
			auto it = std::find_if(m_balls.begin(), m_balls.end(), [](std::pair<MyGui::AbstractFrame*, WindowType>& item) {
				return item.second == Utils::WindowType::Frame;
			});
			it->first->SetPos({0, 0});
			it->first->SetSize(Window::Window::GetVec());
			
			return;
		} else {
			briefcase_size = std::clamp<float>(mark->GetBriefCase().GetWindowSize().x, 500, 800);
				
		    mark->GetBriefCase().SetPos({0, 0});
		    mark->GetBriefCase().SetSize({briefcase_size, static_cast<float>(Window::Window::GetHeight())});
		}
		
		for (auto& ball : m_balls) {
			if (ball.second == WindowType::Frame) {
				ball.first->SetPos({briefcase_size, 0});
				ball.first->SetSize({static_cast<float>(Window::Window::GetWidth()) - briefcase_size, static_cast<float>(Window::Window::GetHeight())});
			}
		}
	}
}
