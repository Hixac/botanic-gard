#pragma once

#include <imgui.h>
#include <imgui_stdlib.h>
#include <imgui_internal.h>

#include <image.hpp>
#include <frame.hpp>
#include <marble.hpp>
#include <image.hpp>
#include <markcontainer.hpp>

#include <memory>

namespace MyGui {

    static bool RoundButton(const char* str_id, Utils::ImageTexture image)
	{
		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		ImVec2 win_size = ImGui::GetWindowSize();

		ImVec2 pos = ImGui::GetCursorPos();
		ImVec2 size {100, 100};
		
		bool click;
		
		click = ImGui::InvisibleButton(str_id, size, ImGuiButtonFlags_FlattenChildren);

		ImU32 col_bg;
		if (ImGui::IsItemHovered())
			col_bg = click ? IM_COL32(145+20, 211, 68+20, 255) : IM_COL32(218-20, 218-20, 218-20, 255);
		else
			col_bg = click ? IM_COL32(145, 211, 68, 255) : IM_COL32(218, 218, 218, 255);

		draw_list->AddImageRounded(reinterpret_cast<void*>(image.GetTextureData()), pos, {pos.x + 100, pos.y + 100}, {0, 0}, {1, 1}, col_bg, 50);

		return click;
	}

	static void SetUpdateForSearch(std::unique_ptr<MyGui::Frame>& frame, MyGui::MarkContainer& marks)
	{
		frame->SetFunction([&]() {
			static std::string name;
			
			ImGui::InputText("имя", &name);

			for (int i = 0; i < marks.GetSize(); ++i) {
				if (marks[i].GetBriefCase().name.substr(0, name.size()) == name) {
					if (ImGui::Button(marks[i].GetBriefCase().name.c_str())) {
					    marks[i].GetBriefCase().Activate();
					}
				}
			}
		});
	}
	
}
