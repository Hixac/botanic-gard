#include <frame.hpp>

#include <marble.hpp>

namespace MyGui {

	Frame::Frame(const char* label, ImVec2 size, ImVec2 pos, ImGuiWindowFlags flags)
		: AbstractFrame(label, size, pos, flags)
	{
		Utils::Marble::Get().Add(this, Utils::WindowType::Frame);
	}

	void Frame::Update()
	{
		ImGui::SetNextWindowPos(m_pos);
		ImGui::SetNextWindowSize(m_size);
		if (ImGui::Begin(m_label, 0, m_flags)) {
			m_fn();

			m_winsize = ImGui::GetWindowSize();
		};
		ImGui::End();
	}
}
