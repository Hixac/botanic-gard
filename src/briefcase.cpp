#include <briefcase.hpp>

#include <filedialog.hpp>
#include <marble.hpp>

#include <imgui.h>
#include <imgui_stdlib.h>

namespace MyGui {

	BriefCase::BriefCase(const char* label, ImVec2 size, ImVec2 pos, ImGuiWindowFlags flags)
		: AbstractFrame(label, size, pos, flags), m_destroy(false)
	{
		Utils::Marble::Get().Add(this, Utils::WindowType::Briefcase);
	}
	
	void BriefCase::Update()
	{
	    Utils::FileDialog::Path path = {
			.out = "ass.jpg",
			.err = Utils::FileDialog::None
		};
		
		ImGui::SetNextWindowPos(m_pos);
		ImGui::SetNextWindowSize(m_size);
		if (ImGui::Begin("Резюме", 0, ImGuiWindowFlags_NoScrollbar)) {
			
			// Need for marble.hpp
			m_winsize = ImGui::GetWindowSize();
			
			if (image.IsSetuped()) {
				image.SetCursorPos({ ImGui::GetWindowSize().x / 16 - 20, 50});
				image.SetSize({300, 300});
				if (image.Button()) {
					path = Utils::FileDialog::Get().Open();
					if (path.err == Utils::FileDialog::None) image.SetupTexture(path.out);
				}
			} else if (path.err == Utils::FileDialog::None) {
				image.SetupTexture(path.out);
			}

			float x_offset = 295 + ImGui::GetWindowSize().x / 16;
			ImVec2 old_cursor_pos = ImGui::GetCursorPos();
			
			ImGui::SameLine();
			ImGui::Text("Имя");
			ImGui::SetCursorPos({x_offset, 80});
			ImGui::InputText("##Имя", &name);

			float padding = 0;
			float counter = 0;
			bool flag = false;
			
			for (int i = 0; i < vec_info.size(); ++i) {
				
				Info& info = vec_info[i];

				ImGui::SetCursorPos({x_offset, 115 + padding});

				ImGui::PushStyleColor(ImGuiCol_FrameBg, {0.1, 0.1, 0.1, 1});
				ImGui::InputText(("##name" + std::to_string(i)).c_str(), &info.name);
				ImGui::PopStyleColor();
				
				if (info.isBig) {
					counter += 10;
					
					ImGui::SetCursorPos({x_offset, 150 + padding});
					ImGui::InputTextMultiline(("##descr" + std::to_string(i)).c_str(), &info.descr);
					
					padding += 250;
					
				} else {
					counter += 1;
					
					ImGui::SetCursorPos({x_offset, 150+ padding});
					ImGui::InputText(("##descr" + std::to_string(i)).c_str(), &info.descr);
					
					padding += 70;
				}

				if (counter > 3 && !flag) {
					x_offset -= 315;
					flag = true;
				}
				
			}

			ImGui::SetCursorPos({x_offset, 115 + padding});
			if (vec_info.size() < 6 && ImGui::Button("+")) {
				vec_info.push_back({.isBig = false});
			}

			ImGui::SameLine();
			if (vec_info.size() < 6 && ImGui::Button("++")) {
				vec_info.push_back({.isBig = true});
			}

			ImGui::SetCursorPos({ImGui::GetWindowSize().x - 170, ImGui::GetWindowSize().y - 35});
			if (ImGui::Button("Удалить точку")) {
				m_destroy = true;
			}
			
		}
		ImGui::End();
	}
	
}
