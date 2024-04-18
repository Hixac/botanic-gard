#include <image.hpp>

namespace MyGui {

	class Image
	{
	public:
		Image() = default;

		void SetupTexture(const char *filename);
		void Update();

		inline void SetCursorPos(ImVec2 pos) { m_cursor_pos = pos; }
		
		inline ImVec2 GetCursorPos() { return m_cursor_pos; }
		inline ImVec2 GetTextureSize() { return m_texture.GetVec(); }

		inline bool IsHovering() { return m_isHovered; }
		
	private:
		Utils::ImageTexture m_texture;

		ImVec2 m_cursor_pos;
		
		bool m_isHovered;
	};
	
}
