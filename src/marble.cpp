#include <marble.hpp>

#include <window.hpp>
#include <base.hpp>
#include <image.hpp>

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

	void Marble::SaveInfo(const std::string& filename, const std::string& pngname, MyGui::MarkContainer& marks)
	{
		SIMPLE_LOG_INFO("Filename " + filename);
		
#if defined(_WIN32)
		std::wstring wfilename = s2ws(filename);
		std::ofstream out(wfilename, std::ios::trunc);
#else
		std::ofstream out(filename, std::ios::trunc);
#endif


		std::string print = "";
	    for (auto& mark : marks.GetVector()) {
			print += "{";
			print += mark.GetLabel();
			print += ",";
			print += std::to_string(mark.GetPos().x);
			print += ",";
			print += std::to_string(mark.GetPos().y);
			print += ",";
			print += mark.GetBriefCase().name;
			print += ",";
			print += mark.GetBriefCase().image.GetFilename();
			for (auto& info : mark.GetBriefCase().vec_info) {
			    print += "{";
				print += info.name;
				print += ",";
				print += info.descr;
				print += ",";
				print += info.isBig ? "1" : "0";
				print += "}";
			}
			print += "};"; // {[label],[x],[y],[name],{[name],[descr],[is big]},[same structs]...};
		}

		out << print + "\n";
		out << pngname;

//#if defined(_WIN32)
//		std::wstring wfname = s2ws(filename);
//		std::fstream png(wfname);
//#else
//		std::fstream png(filename);
//#endif
//		if (!png.is_open()) assert(false && "File doesn't opened");
//
//		out << png.rdbuf(); // copying photo to store it within one file
	}

	MyGui::MarkContainer Marble::LoadInfo(const std::string& filename, std::string& out_pngname)
    {
#if defined(_WIN32)
		std::wstring wfname = s2ws(filename);
		std::fstream in(wfname);
#else
		std::fstream in(filename);
#endif
		if (!in.is_open()) assert(false && "File doesn't opened");

		std::string line;
		std::string text;

		std::getline(in, line); // get the marks
		
		int count = 0;

		std::string label = "";
		ImVec2 pos;
		std::string name = "";
		std::string fname = "";
		std::vector<MyGui::Info> vec_info;
		MyGui::MarkContainer marks;

		for (size_t i = 0; i < line.size(); ) {
			char c = line[i];

			switch (c)
			{
			case '{': {
				count++;

				if (count == 1) {
					for (i += 1; line[i] != ','; ++i) {
						label += line[i];
					}
					i += 1; // to avoid ','

					std::string x = "";
					for (; line[i] != ','; ++i) {
						x += line[i];
					}
					pos.x = std::stof(x);
					i += 1; // to avoid ','

					std::string y = "";
					for (; line[i] != ','; ++i) {
						y += line[i];
					}
					pos.y = std::stof(y);
					i += 1; // to avoid ','

					for (; line[i] != ','; ++i) {
						name += line[i];
					}
					i += 1;

					for (; line[i] != '{' && line[i] != '}'; ++i) {
						fname += line[i];
					}

				}
				else {
					MyGui::Info info{ .name = "", .descr = "", .isBig = false};
					int fields = 0;
					for (++i; line[i] != '}'; ++i) {
						c = line[i];
						if (c == ',') {
							fields++;
							continue;
						}
						if (fields > 3) assert(false && "bad programming");

						if (fields == 0) {
							info.name += line[i];
						}
						if (fields == 1) {
							info.descr += line[i];
						}
						if (fields == 2) {
							info.isBig = bool(line[i] - '0');
						}
					}
					i += 1; // to avoid '}'
					vec_info.push_back(info);
				}

			} continue;
			case '}': {
				i += 1;
			} continue;
			case ';': {
				marks.Add(label, pos, name, fname, vec_info);
				count = 0;

				label.clear();
				vec_info.clear();
				name.clear();
				fname.clear();

				i += 1;
			} continue;
			}
		}
		
		std::getline(in, out_pngname); // get the png

		return marks;
	}
	
}
