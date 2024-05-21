#include <image_render.hpp>

#include <window.hpp>

namespace MyGui {

	void Image::SetupTexture(const char *filename)
	{
		m_filename = filename;
		m_texture.CreateTexture(filename);
		
		m_size = GetTextureSize();
		m_isSetuped = true;
	}

	void Image::Update()
	{
		ImGui::SetCursorPos(m_cursor_pos);
		ImGui::Image((void*)(intptr_t)m_texture.GetTextureData(), m_size);

		m_isHovered = ImGui::IsItemHovered();
	}

	bool Image::Button()
	{
		ImGui::SetCursorPos(m_cursor_pos);
		bool ret = ImGui::ImageButton((void*)(intptr_t)m_texture.GetTextureData(), m_size);

		m_isHovered = ImGui::IsItemHovered();

		return ret;
	}
	
}
