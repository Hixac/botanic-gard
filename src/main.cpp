#include <window.hpp>

#include <imgui_stdlib.h>

#include <mygui.hpp>
#include <frame.hpp>
#include <filedialog.hpp>
#include <mark.hpp>
#include <markcontainer.hpp>
#include <marble.hpp>

#include <base.hpp>

#include <algorithm>

int main(void)
{
	Window::Window win("Фруктовый сад", 1600, 800);

	MyGui::Image image;
	Utils::ImageTexture button_image;
	button_image.CreateTexture("lupa.png");
	
	std::unique_ptr<MyGui::Frame> image_loop(new MyGui::Frame("ImageRender", win.GetVec(), {0, 0}, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoScrollbar));

	std::unique_ptr<MyGui::Frame> search_loop(new MyGui::Frame("SearchRoom", {300, 300}, {float(win.GetWidth() - 375), 85}, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar, false));
	
	MyGui::MarkContainer marks;

	ImVec2 buffer_mouse_pos;
	ImVec2 delta_mouse_pos;
	ImVec2 sum_mouse_pos;

	float scale = 1;

	std::vector<ImVec2> vec_abs_pos;

	std::string search_name = "";
	bool search_menu = false;
	bool is_rb_pressed = false;
	
    MyGui::SetUpdateForSearch(search_loop, marks);
	
	image_loop->SetFunction([&](){

		vec_abs_pos.clear();
		marks.ForAll([&](auto& m) {
			vec_abs_pos.push_back(m.GetAbsPos(image));
		});
		
		float image_x = (ImGui::GetWindowSize().x - image.GetTexture().GetVec().x) > 0 ?
			(ImGui::GetWindowSize().x - image.GetTexture().GetVec().x) * 0.5f : 0;
		
		float image_y = (ImGui::GetWindowSize().y - image.GetTexture().GetVec().y) > 0 ?
			(ImGui::GetWindowSize().y - image.GetTexture().GetVec().y) * 0.5f : 30;
		
		ImVec2 image_pos = { image_x - sum_mouse_pos.x, image_y - sum_mouse_pos.y};
		
		if (Window::Window::GetRightMouseAbsPress()) {
		    delta_mouse_pos = { Window::Window::GetMousePosition().x - buffer_mouse_pos.x,
				Window::Window::GetMousePosition().y - buffer_mouse_pos.y};
			
			sum_mouse_pos = { sum_mouse_pos.x + delta_mouse_pos.x, sum_mouse_pos.y + delta_mouse_pos.y };

			SIMPLE_LOG_INFO("Mouse position: " + std::to_string(buffer_mouse_pos.x) + ", " + std::to_string(buffer_mouse_pos.y));
		}

		if (Window::Window::GetLeftControlPress()) {
			float scroll_y = Window::Window::GetScrollOffset().y * 50;
			
			scale = std::clamp<float>(std::abs(scale - scroll_y / ImGui::GetWindowHeight()), 0.0615, 10);
			image.SetSize({image.GetTexture().GetWidth() * scale, image.GetTexture().GetHeight() * scale});
			
			SIMPLE_LOG_INFO("Scaling: " + std::to_string(scale));
		}

		if (image.IsSetuped()) {
			image.SetCursorPos(image_pos);
			image.Update();
		}
		
		if (ImGui::BeginMenuBar()) {
			if (ImGui::MenuItem("Открыть фото")) {
				auto path = Utils::FileDialog::Get().Open();

				if (path.err == Utils::FileDialog::None) {
					sum_mouse_pos = {0, 0};
					image.SetupTexture(path.out);
					marks.Clear();
				} else {
					// TODO: MAKE NOTIFY
				}
			}
			ImGui::Separator();
			if (ImGui::MenuItem("Сохранить метки") && image.IsSetuped()) { // image.IsSetuped very important to use!
				auto path = Utils::FileDialog::Get().Save();

				if (path.err == Utils::FileDialog::None) {
					Utils::Marble::Get().SaveInfo(path.out, image, marks);
				}
				else {
					// TODO: MAKE NOTIFY
				}
			}
			ImGui::Separator();
            // we load not only marks but also and a photo within one file!
			// not probably fastest solution but very comfy to do it ig.
			if (ImGui::MenuItem("Загрузить материал")) { 
				auto path = Utils::FileDialog::Get().Open({"Информационная единица", "info"});

				if (path.err == Utils::FileDialog::None) {
					marks = Utils::Marble::Get().LoadInfo(path.out, image);

				} else {
					// TODO: MAKE NOTIFY
				}
			}
			ImGui::Separator();
			if (ImGui::MenuItem("Поиск")) {
				ImGui::InputText("ключевое слово", &search_name);

				std::vector<std::string> vec_names;
				for (auto& m : marks.GetVector()) {
					vec_names.push_back(m.GetBriefCase().name);
				}

				static int value = 0;
				static std::string preview_name = vec_names.empty() ? "Ничего" : vec_names[value];
				
				if (ImGui::BeginCombo("Items", preview_name.c_str())) {
					for (size_t i = 0; i < vec_names.size(); i++) {
						const bool is_selected = (value == i);
						if (ImGui::Selectable(vec_names[i].c_str(), is_selected))
							value = i;
				
						if (is_selected)
							ImGui::SetItemDefaultFocus();
					}
					ImGui::EndCombo();
				}
			}
			ImGui::Separator();
			
			ImGui::EndMenuBar();
		}
		
		// PLACE ABOVE MARK FACTORY BECAUSE IT PROC THEIR CLICK
		for (int i = 0; i < marks.GetSize(); ++i) {
			
		    if (marks[i].ToDestroy()) { // DO NOT NEED BUT IT MAY BE USEFUL IN FUTURE SO I DON'T REMOVE IT
				SIMPLE_LOG_INFO("Destroyed!");
				marks(i);
				vec_abs_pos.erase(vec_abs_pos.begin() + i);
				MyGui::BriefCase::Disactivate();
				
			    continue;
			}

			marks[i].Update();

			marks[i].SetPos({vec_abs_pos[i].x * image.GetSize().x + image.GetCursorPos().x, vec_abs_pos[i].y * image.GetSize().y + image.GetCursorPos().y});
		}
		
		// PLEASE DON'T CREATE MORE MARKS
		if (Window::Window::GetLeftMouseRelease() && !MyGui::BriefCase::GetActivation() && image.IsHovering() && !marks.Any()) {
			ImVec2 pos = {Window::Window::GetMousePosition().x - 10 + ImGui::GetScrollX(), Window::Window::GetMousePosition().y - 15 + ImGui::GetScrollY()};
			marks.Add(pos);
		    RAW_LOG_INFO("Added mark with pos: " << std::to_string(pos.x) << ", " << std::to_string(pos.y));
			
		} else if (Window::Window::GetLeftMouseRelease() && ImGui::IsWindowHovered() && MyGui::BriefCase::GetActivation() && !marks.Any()) {
			MyGui::BriefCase::Disactivate();
		}

		if (search_menu) {
			ImGui::SetNextWindowBgAlpha(1);
		    search_loop->Update();
		}	    

		ImVec2 temp_cur = ImGui::GetCursorPos();
		ImGui::SetCursorPos({ImGui::GetWindowSize().x - 125 + Utils::Marble::Get().BriefcaseSize(), 50});
	    if (MyGui::RoundButton("Button", button_image)) {
			search_menu = !search_menu;
			is_rb_pressed = true;
		}
		ImGui::SetCursorPos(temp_cur);
		
		if (!is_rb_pressed && !search_loop->IsWindowHovered() && Window::Window::GetLeftMouseRelease()) {
	        search_menu = false;
	    }

		is_rb_pressed = false;
		buffer_mouse_pos = { Window::Window::GetMousePosition().x, Window::Window::GetMousePosition().y };
		delta_mouse_pos  = {0, 0};
	});
	
	win.OnUpdateCallBack([&]() {

		search_loop->SetPos({float(win.GetWidth() - 375), 85});
		
	    if (MyGui::BriefCase::GetActivation()) {
			MyGui::BriefCase::GetActivation()->Update();
		}

		image_loop->Update();
		
		Utils::Marble::Get().DoPortionCalc();
		
	});
	
	return 0; // Программа закрыта без ошибок
}
