#pragma once

#include <functional>
#include <imgui.h>

namespace MyGui {

	class AbstractFrame
	{
	public:
		virtual void Update() = 0;

	    inline void SetSize(const ImVec2 size) { if (size.x > 0 && size.y > 0) m_size = size; }
	    inline void SetPos(const ImVec2 pos)   { m_pos = pos; }

		inline ImVec2 GetSize() const { return m_size; }
		inline ImVec2 GetPos()  const { return m_pos;  }

		inline ImVec2 GetWindowSize() const { return m_winsize; }
		
    protected:

		const char* m_label;
		
		ImVec2 m_pos;
		ImVec2 m_size;
		ImVec2 m_winsize;
		
		ImGuiWindowFlags m_flags;

		AbstractFrame(const char* label, ImVec2 size, ImVec2 pos, ImGuiWindowFlags flags = 0)
			: m_label(label), m_size(size), m_pos(pos), m_flags(flags)
		{ }
		virtual ~AbstractFrame() = default;
		
	};
	
	class Frame : public AbstractFrame
	{
	public:
		Frame(const char* label, ImVec2 size, ImVec2 pos, ImGuiWindowFlags flags = 0);
		
		void Update() override;
		inline void SetFunction(std::function<void()> fn) { m_fn = fn; }

	private:
		std::function<void()> m_fn;
	};
	
}
