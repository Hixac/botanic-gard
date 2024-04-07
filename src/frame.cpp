
#include <frame.hpp>

namespace MyGui {

	Frame::Frame(const char* label, ImVec2 size, ImVec2 pos, ImGuiWindowFlags flags)
		: m_label(label), m_size(size), m_pos(pos), m_flags(flags)
	{ }

	void Frame::Update()
	{
		ImGui::SetNextWindowSize(m_size);
		if (ImGui::Begin(m_label)) {
			ImGui::SetWindowPos(m_pos);
			
			m_fn();

			ImGui::End();
		};
	}
}
