#include <markcontainer.hpp>

namespace MyGui {
	
	void MarkContainer::Add(ImVec2 pos)
	{
		Mark mark(std::to_string(m_marks.size() + 1), pos); // fix me
		m_marks.push_back(std::move(mark));
	}

	bool MarkContainer::Any(Mark* mark)
	{
		for (auto& m : m_marks) {
			if (m.IsHovered()) {
				mark = &m;
				return true;
			}
		}

		return false;
	}
	
}
