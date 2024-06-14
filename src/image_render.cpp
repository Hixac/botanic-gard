#include <image_render.hpp>

#include <window.hpp>

#include <base.hpp>

namespace MyGui {

	void Image::SetupTexture(const char *filename)
	{
		m_filename = filename;
		m_texture.CreateTexture(filename);

		SIMPLE_LOG_INFO("File named " + std::string(filename) + " has initialized!");
		SIMPLE_LOG_INFO("With size: " + std::to_string(m_texture.GetWidth()) + "x" + std::to_string(m_texture.GetHeight()));
		
		m_size = m_texture.GetVec();
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
