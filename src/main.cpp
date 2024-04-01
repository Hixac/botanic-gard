#include <window.hpp>

#include <imgui.h>

int main(void)
{
	Window::Window win("Фруктовый сад", 640, 480);

	win.OnUpdateCallBack([]() {
		
		if (ImGui::Begin("Win")) {

			ImGui::Text("Check");

			ImGui::End();
		}
		
	});
	
	return 0; // Программа закрыта без ошибок
}

// TODO: Image render class
// TODO: Mark adder
// TODO: Describer for mark
