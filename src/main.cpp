#include <window.hpp>

#include <frame.hpp>
#include <image.hpp>
#include <filedialog.hpp>

int main(void)
{
	Window::Window win("Фруктовый сад", 640, 480);

	Utils::ImageTexture image;
	
	MyGui::Frame image_render("ImageRender", win.GetVec(), {140, 0});
	MyGui::Frame marker("Marker", {win.GetVec().x - (640 - 500), win.GetVec().y }, {0, 0});
	
	marker.SetFunction([&](){

		if (ImGui::Button("Открыть фото")) {
			auto path = Utils::FileDialog::Get().Open();

			if (path.err == Utils::FileDialog::None) {
				image.CreateTexture(path.out.get());
			} else {
				
			}
		}
		
	});
			
	image_render.SetFunction([&](){

		ImGui::Image((void*)(intptr_t)image.GetTextureData(), image.GetVec());
			
	});
	
	win.OnUpdateCallBack([&]() {
		
		marker.Update();
		image_render.Update();
		
	});
	
	return 0; // Программа закрыта без ошибок
}

// TODO: Image render class
// TODO: Mark adder
// TODO: Describer for mark
