#pragma once

#include <imgui.h>
#include <imgui_stdlib.h>
#include <imgui_internal.h>

#include <image.hpp>
#include <frame.hpp>
#include <marble.hpp>
#include <image.hpp>
#include <markcontainer.hpp>
#include <window.hpp>

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

	static void DrawRectangle(ImVec2 first_pos)
	{
		ImDrawList* draw_list = ImGui::GetWindowDrawList();

		ImVec2 pos = Window::Window::GetMousePosition();

		draw_list->AddRectFilled(first_pos, pos, ImGui::GetColorU32({0, 0, 0, 0.5}));
	}

	// Why not class? :| :PP
	inline static float first_time = 0;
	inline static bool timer_started = false;
	static void StartDrawRectTimer(float time)
	{
	    first_time = ImGui::GetTime() + time;
		timer_started = true;
	}

	[[nodiscard]] static bool CheckDrawRectTimer()
	{
		return timer_started ? ImGui::GetTime() > first_time : false;
	}
	
	static void EraseMarks(ImVec2 first, ImVec2 last, MyGui::MarkContainer& marks)
	{
		for (int i = 0; i < marks.GetSize(); ++i) {
		    ImVec2 pos = marks[i].GetPos();
			if (first.x < pos.x && last.x > pos.x && first.y < pos.y && last.y > pos.y)
			    marks[i].GetBriefCase().Destroy();
		}
	}

	inline static MyGui::MarkContainer copy_marks;
	static void CopyMarks(ImVec2 first, ImVec2 last, MyGui::MarkContainer& marks, ImVec2 offset)
	{
		copy_marks.Clear();
		for (int i = 0; i < marks.GetSize(); ++i) {
		    ImVec2 pos = marks[i].GetPos();
			if (first.x < pos.x && last.x > pos.x && first.y < pos.y && last.y > pos.y)
			    copy_marks.Add(marks[i], {pos.x - first.x, pos.y - first.y});
		}
	}
	
}
