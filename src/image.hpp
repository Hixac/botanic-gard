#pragma once

#include <GLES3/gl3.h>

#include <imgui.h>

namespace Utils {

	class ImageTexture
	{
	public:
		ImageTexture() = default;

		void CreateTexture(const char* filename);
		
		GLuint GetTextureData() { return m_texture; }
		
		int GetWidth() { return m_width; }
		int GetHeight() { return m_height; }

		// Долбаёбы не додумались сделать ImVec2 для int
	    ImVec2 GetVec() { return {static_cast<float>(m_width), static_cast<float>(m_height)}; }
		
	private:
		GLuint m_texture;
		int m_width, m_height;
	};
	
}
