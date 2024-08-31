#pragma once

#include <imgui.h>
#include <windows_utils.hpp>

namespace Utils {

	class ImageTexture
	{
	public:
		ImageTexture() = default;

		void CreateTexture(const char* filename);

		unsigned int GetTextureData() { return m_texture; }
		
		int GetWidth() { return m_width; }
		int GetHeight() { return m_height; }
		
	    ImVec2 GetVec() { return {static_cast<float>(m_width), static_cast<float>(m_height)}; }
		
	private:
		unsigned int m_texture;
		
		int m_width, m_height;
	};
	
}
