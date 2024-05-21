#include <marble.hpp>

#include <window.hpp>
#include <base.hpp>

#include <fstream>
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

	void Marble::SaveInfo(const std::string& filename, MyGui::MarkContainer& marks)
	{
		SIMPLE_LOG_INFO("Filename " + filename);
		
		std::ofstream out("HELLO_ME_HERE.info", std::ios::trunc);

		std::string print = "";
	    for (auto& mark : marks.GetVector()) {
			print += "{ ";
			print += mark.GetLabel();
			print += ", ";
			print += std::to_string(mark.GetPos().x);
			print += ", ";
			print += std::to_string(mark.GetPos().y);
			for (auto& info : mark.GetBriefCase().vec_info) {
			    print += ", { ";
				print += info.name;
				print += ", ";
				print += info.isBig ? "1" : "0";
				print += ", ";
				print += info.descr;
				print += " }";
			}
			print += " }; "; // { label, x, y };
		} // need to add some more info to save

		out << print + "\n";

		std::fstream png(filename);

		out << png.rdbuf(); // copying photo to store it within one file
	}

	void Marble::LoadInfo(const std::string& filename)
    {
		// { [label], [x], [y], { [name], [is big], [descr]}, [same structs]...}; <-- reached the end of one mark
		std::fstream in(filename);

		
		
	}
	
}
