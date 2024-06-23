#include <marble.hpp>

#include <window.hpp>
#include <base.hpp>
#include <image.hpp>

#include <fstream>
#include <algorithm>

namespace Utils {
	
	void Marble::DoPortionCalc()
	{
	    MyGui::BriefCase* briefcase = MyGui::BriefCase::GetActivation();
		if (briefcase == nullptr) { // restore all the shit that I made (im so sorry for this)
			auto it = std::find_if(m_balls.begin(), m_balls.end(), [](std::pair<MyGui::AbstractFrame*, WindowType>& item) {
				return item.second == Utils::WindowType::Frame;
			});
			it->first->SetPos({0, 0});
			it->first->SetSize(Window::Window::GetVec());

			m_briefcase_size_x = 0;
			
			return;
		}
		
		m_is_acivated_briefcase = true;
		
	    m_briefcase_size_x = std::clamp<float>(briefcase->GetWindowSize().x, 500, 800);
				
	    briefcase->SetPos({0, 0});
	    briefcase->SetSize({m_briefcase_size_x, static_cast<float>(Window::Window::GetHeight())});
		
		for (auto& ball : m_balls) {
			if (ball.second == WindowType::Frame) {
				ball.first->SetPos({m_briefcase_size_x, 0});
				ball.first->SetSize({static_cast<float>(Window::Window::GetWidth()) - m_briefcase_size_x, static_cast<float>(Window::Window::GetHeight())});
			}
		}
	}

	void Marble::SaveInfo(const std::string& filename, MyGui::Image& image, MyGui::MarkContainer& marks)
	{
		SIMPLE_LOG_INFO("Filename " + filename);
		
#if defined(_WIN32)
		std::wstring wfilename = s2ws(filename);
		std::ofstream out(wfilename, std::ios::trunc);
#else
		std::ofstream out(filename, std::ios::trunc);
#endif
		
		ImVec2 cur_pos = image.GetCursorPos();

		RAW_LOG_INFO("File is saving!");
		RAW_LOG_INFO("Current cursor position: " << std::to_string(cur_pos.x) << ", " << std::to_string(cur_pos.y));
		
		std::string print = "";
	    for (auto& mark : marks.GetVector()) {
			ImVec2 rel_pos = {(mark.GetPos().x - cur_pos.x)/image.GetTexture().GetWidth(), (mark.GetPos().y - cur_pos.y)/image.GetTexture().GetHeight()};
			print += "{";
			print += mark.GetLabel();
			print += ",";
		    print += std::to_string(rel_pos.x);
			print += ",";
			print += std::to_string(rel_pos.y);
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
			print += "};"; // {[label],[x <- : (0; 1)],[y <- : (0; 1)],[name],{[name],[descr],[is big]},[same structs]...};
		}

		out << print << "\n";
#if defined(_WIN32)
		std::wstring wpname = s2ws(image.GetFilename());
		std::ifstream png(wpname, std::ios::binary);
#else
		std::ifstream png(image.GetFilename(), std::ios::binary);
#endif
	    assert(png && "File didn't opened");

		out << png.rdbuf(); // copying photo to store it within one file
		
		out.close();
		png.close();
	}

	MyGui::MarkContainer Marble::LoadInfo(const std::string& filename, MyGui::Image& image)
    {

		std::ofstream out("./out.png", std::ios::binary);
		
#if defined(_WIN32)
		std::wstring wfname = s2ws(filename, std::ios::binary);
		std::ifstream png(wfname);
#else
		std::ifstream png(filename, std::ios::binary);
#endif
		assert(png && "File doesn't found");
		std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(png), {});

		int slice;
		for (int i = 0; i < buffer.size(); ++i) {
			if (buffer[i] == '\n') {
				slice = i + 1;
				break;
			}
		}

		buffer.erase(buffer.begin(), buffer.begin() + slice);
		std::copy(buffer.begin(), buffer.end(), std::ostreambuf_iterator<char>(out));

		out.close();
		png.close();
		
		image.SetupTexture("./out.png");
		
#if defined(_WIN32)
		std::wstring wfname = s2ws(filename);
		std::ifstream in(wfname);
#else
		std::ifstream in(filename);
#endif
	    assert(in.is_open() && "File doesn't opened");

		std::string line;
		std::string text;

		std::getline(in, line); // get the marks
		
		int count = 0;
		ImVec2 cur_pos = image.GetCursorPos();
		
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
				marks.Add(label, {pos.x * image.GetTexture().GetWidth() + cur_pos.x, pos.y * image.GetTexture().GetHeight() + cur_pos.y}, name, fname, vec_info);
				RAW_LOG_INFO("Added new mark, pos: " << std::to_string(pos.x) << ", " << std::to_string(pos.y) << "; " << std::endl							 << "name: " << name << " file: " << fname);
					
				count = 0;

				label.clear();
				vec_info.clear();
				name.clear();
				fname.clear();

				i += 1;
			} continue;
			}
		}
		
		return marks;
	}
	
}
