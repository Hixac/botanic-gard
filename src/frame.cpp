#include <frame.hpp>

#include <marble.hpp>

namespace MyGui {

	Frame::Frame(const char* label, ImVec2 size, ImVec2 pos, ImGuiWindowFlags flags, bool marble_add)
		: AbstractFrame(label, size, pos, flags), m_child(!marble_add)
	{
	    if (marble_add) Utils::Marble::Get().Add(this, Utils::WindowType::Frame);
	}

	void Frame::Update()
	{
		ImGui::SetNextWindowPos(m_pos);
		ImGui::SetNextWindowSize(m_size);
		if ((m_child && ImGui::BeginChild(m_label, m_size, ImGuiChildFlags_Border, m_flags)) || (!m_child && ImGui::Begin(m_label, 0, m_flags))) {
			m_fn();

			m_is_hovered = ImGui::IsWindowHovered();
			
			m_winsize = ImGui::GetWindowSize();
		}
		if (m_child) ImGui::EndChild();
	    else ImGui::End();
	}
}
