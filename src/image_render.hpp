#include <image.hpp>

#include <string>

namespace MyGui {

	class Image
	{
	public:
		Image() : m_isSetuped(false), m_isHovered(false) { }

		void SetupTexture(const char *filename);
		
		void Update();
		bool Button();

		inline void SetSize(ImVec2 size) { m_size = size; }
		inline void SetCursorPos(ImVec2 pos) { m_cursor_pos = pos; }

		// May be dangerous because of needing of setuping
		inline ImVec2 GetCursorPos() { return m_cursor_pos; }
		inline ImVec2 GetTextureSize() { return m_texture.GetVec(); }
		
		inline const std::string& GetFilename() { return m_filename; }
		
		inline bool IsHovering() { return m_isHovered; }
		inline bool IsSetuped() { return m_isSetuped; }
		
	private:
		Utils::ImageTexture m_texture;

		std::string m_filename;
		
		ImVec2 m_size;
		ImVec2 m_cursor_pos;

		bool m_isSetuped;
		bool m_isHovered;
	};
	
}
