#include <image_render.hpp>

#include <window.hpp>

namespace MyGui {

	void Image::SetupTexture(const char *filename)
	{
		m_texture.CreateTexture(filename);
	}

	void Image::Update()
	{
		ImGui::SetCursorPos(m_cursor_pos);
		ImGui::Image((void*)(intptr_t)m_texture.GetTextureData(), GetTextureSize());

		m_isHovered = ImGui::IsItemHovered();
	}
	
}
