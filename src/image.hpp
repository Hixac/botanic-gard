#pragma once

#include <imgui.h>

#if defined(_WIN32)
#include <windows.h>
#include <string>

static std::wstring s2ws(const std::string& str)
{
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}
#endif

namespace Utils {

	class ImageTexture
	{
	public:
		ImageTexture() = default;

		void CreateTexture(const char* filename);
		
		unsigned int GetTextureData() { return m_texture; }
		
		int GetWidth() { return m_width; }
		int GetHeight() { return m_height; }

		// Долбаёбы не додумались сделать ImVec2 для int
	    ImVec2 GetVec() { return {static_cast<float>(m_width), static_cast<float>(m_height)}; }
		
	private:
		unsigned int m_texture;
		int m_width, m_height;
	};
	
}
