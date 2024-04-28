#include <briefcase.hpp>

#include <filedialog.hpp>
#include <marble.hpp>

#include <imgui.h>
#include <imgui_stdlib.h>

namespace MyGui {

	BriefCase::BriefCase(const char* label, ImVec2 size, ImVec2 pos, ImGuiWindowFlags flags)
		: AbstractFrame(label, size, pos, flags)
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
		if (ImGui::Begin("Резюме")) {

			m_winsize = ImGui::GetWindowSize();
			
			if (image.IsSetuped()) {
				image.SetCursorPos({ this->GetWindowSize().x / 16, 50});
				image.SetSize({300, 300});
				if (image.Button()) {
					path = Utils::FileDialog::Get().Open();
					if (path.err == Utils::FileDialog::None) image.SetupTexture(path.out);
				}
			} else if (path.err == Utils::FileDialog::None) {
				image.SetupTexture(path.out);
			}

			ImGui::SameLine();
			ImGui::Text("Имя");
			ImGui::InputText("##Имя", &name);
			ImGui::Text("Описание");
			ImGui::InputTextMultiline("##Описание", &description);
		}
		ImGui::End();
	}
	
}
