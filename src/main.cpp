#include "imgui.h"
#include <window.hpp>

#include <frame.hpp>
#include <filedialog.hpp>
#include <mark.hpp>
#include <markcontainer.hpp>
#include <marble.hpp>

#include <base.hpp>

int main(void)
{
	Window::Window win("Фруктовый сад", 1600, 800);

	MyGui::Image image;
	
	std::unique_ptr<MyGui::Frame> image_loop(new MyGui::Frame("ImageRender", win.GetVec(), {0, 0},
						ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_MenuBar
															  | ImGuiWindowFlags_HorizontalScrollbar));

    MyGui::Mark* marked = nullptr;
	MyGui::MarkContainer marks;

	image_loop->SetFunction([&](){
		
		if (image.IsSetuped()) {
			image.SetCursorPos({(float)win.GetWidth() / 2 - (float)image.GetTextureSize().x / 2,
					(float)win.GetHeight() / 2 - (float)image.GetTextureSize().y / 2 - 30});
			image.Update();
		}
		
		if (ImGui::BeginMenuBar()) {
			if (ImGui::MenuItem("Открыть фото")) {
				auto path = Utils::FileDialog::Get().Open();

				if (path.err == Utils::FileDialog::None) {
					image.SetupTexture(path.out);
					marks.Clear();
				} else {
					// TODO: MAKE NOTIFY
				}
			}
			ImGui::Separator();
			
			ImGui::EndMenuBar();
		}

		// PLACE ABOVE MARK FACTORY BECAUSE IT PROC THEIR CLICK
		for (auto& mark : marks()) {
		    if (mark.Update()) {
				SIMPLE_LOG_INFO("Marked!");
				marked = marked ? nullptr : &mark; // good way to make turns, lol!
			}
		}
		
		// PLEASE DON'T CREATE MORE MARKS
		if (Window::Window::GetLeftMouseDown() && !marked && image.IsHovering() && !marks.Any()) {
			marks.Add({Window::Window::GetMousePosition().x - 10 + ImGui::GetScrollX(), Window::Window::GetMousePosition().y - 15 + ImGui::GetScrollY()});
		} else if (Window::Window::GetLeftMouseDown() && ImGui::IsWindowHovered() && marked && !marks.Any()) {
			marked = nullptr; // remove marked; better to remove this unintuitive shit
		}
		
	});
	
	win.OnUpdateCallBack([&]() {
		if (marked)
			marked->UpdateFun();
		
		image_loop->Update();

		Utils::Marble::Get().DoPortionCalc(marked); // Do the check if marked has been clicked
	});
	
	return 0; // Программа закрыта без ошибок
}

// TODO: Describer for mark
