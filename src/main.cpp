#include <window.hpp>

#include <frame.hpp>
#include <image.hpp>
#include <filedialog.hpp>

int main(void)
{
	Window::Window win("Фруктовый сад", 640, 480);

	Utils::ImageTexture image;
	
	MyGui::Frame image_render("ImageRender", win.GetVec(), {0, 0}, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_MenuBar);
	// MyGui::Frame marker("Marker", {win.GetVec().x / 5, win.GetVec().y }, {0, 0}, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
	
	// marker.SetFunction([&](){

	// 	marker.SetSize({ win.GetVec().x / 4, win.GetVec().y });
		
	// 	if (ImGui::Button("Открыть фото")) {
	// 		auto path = Utils::FileDialog::Get().Open();

	// 		if (path.err == Utils::FileDialog::None) {
	// 			image.CreateTexture(path.out);
	// 		} else {
	// 			// TODO: MAKE NOTIFY
	// 		}
	// 	}
		
	// });
			
	image_render.SetFunction([&](){

		image_render.SetSize(win.GetVec());
		// image_render.SetPos({win.GetVec().x / 4, 0});

		if (ImGui::BeginMenuBar()) {
			if (ImGui::MenuItem("Открыть фото")) {
				auto path = Utils::FileDialog::Get().Open();

				if (path.err == Utils::FileDialog::None) {
					image.CreateTexture(path.out);
				} else {
					// TODO: MAKE NOTIFY
				}
			}
			ImGui::Separator();
			
			ImGui::EndMenuBar();
		}
		
		ImGui::Image((void*)(intptr_t)image.GetTextureData(), win.GetVec());
			
	});
	
	win.OnUpdateCallBack([&]() {
		
		// marker.Update();
		image_render.Update();
		
	});
	
	return 0; // Программа закрыта без ошибок
}

// TODO: Mark adder
// TODO: Describer for mark
