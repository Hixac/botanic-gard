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
			if (ImGui::MenuItem("Сохранить метки") && image.IsSetuped()) { // image.IsSetuped very important to use!
				Utils::Marble::Get().SaveInfo(image.GetFilename(), marks);
			}
			ImGui::Separator();
            // we load not only marks but also and a photo within one file!
			// not probably fastest solution but very comfy to do it ig.
			if (ImGui::MenuItem("Загрузить материал")) { 
				auto path = Utils::FileDialog::Get().Open({"Информационная единица", "info"});

				if (path.err == Utils::FileDialog::None) {
					Utils::Marble::Get().LoadInfo(path.out);
				} else {
					// TODO: MAKE NOTIFY
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
				marked = nullptr;
				
			    continue;
			}

			if (marks[i].Update()) {
				SIMPLE_LOG_INFO("Marked!");
				marked = marked ? nullptr : &marks[i]; // good way to make turns, lol!
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

	    if (marked) {	 
			marked->UpdateFun();
		}
		
		image_loop->Update();

		Utils::Marble::Get().DoPortionCalc(marked);
		
	});
	
	return 0; // Программа закрыта без ошибок
}

// TODO: Describer for mark
