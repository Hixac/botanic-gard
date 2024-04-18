#include <window.hpp>

#include <frame.hpp>
#include <image_render.hpp>
#include <filedialog.hpp>
#include <mark.hpp>

#include <base.hpp>

int main(void)
{
	Window::Window win("Фруктовый сад", 640, 480);

	MyGui::Image image;
	
	MyGui::Frame image_loop("ImageRender", win.GetVec(), {0, 0}, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_MenuBar);

	MyGui::Mark* marked;
	MyGui::MarkContainer marks;
	
	image_loop.SetFunction([&](){

		image_loop.SetSize(win.GetVec());

		image.SetCursorPos({(float)win.GetWidth() / 2 - (float)image.GetTextureSize().x / 2,
				(float)win.GetHeight() / 2 - (float)image.GetTextureSize().y / 2 - 28});
		image.Update();
		
		if (ImGui::BeginMenuBar()) {
			if (ImGui::MenuItem("Открыть фото")) {
				auto path = Utils::FileDialog::Get().Open();

				if (path.err == Utils::FileDialog::None) {
					image.SetupTexture(path.out);
				} else {
					// TODO: MAKE NOTIFY
				}
			}
			ImGui::Separator();
			
			ImGui::EndMenuBar();
		}

		// PLACE ABOVE MARK FACTORY BECAUSE IT PROC THEIR CLICK
		for (auto& mark : marks()) {
		    if (mark.Update()) marked = &mark;
		}
		
		// PLEASE DON'T CREATE MORE MARKS
		if (Window::Window::GetLeftMouseDown() && image.IsHovering() && !marks.Any()) {
			marks.Add(Window::Window::GetMousePosition(), [&](){
				if (ImGui::Begin("New window!", 0, ImGuiWindowFlags_NoCollapse)) {
					ImGui::Text("BREAK THRUUUUUUUU PLEASE WORK FOR FUCKING SAKE!!");
					
					ImGui::End();
				}
			});
		}		
		
	});
	
	win.OnUpdateCallBack([&]() {
		
		image_loop.Update();

		if (!marked) {
			marked->UpdateFun();
		}
		
	});
	
	return 0; // Программа закрыта без ошибок
}

// TODO: Describer for mark
