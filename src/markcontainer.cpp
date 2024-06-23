#include <markcontainer.hpp>

namespace MyGui {
	
	void MarkContainer::Add(ImVec2 pos)
	{
		Mark mark(std::to_string(m_marks.size() + 1 + m_deletes), pos);
		m_marks.push_back(std::move(mark));
	}

	void MarkContainer::Add(std::string label, ImVec2 pos, std::string name, std::string filename, std::vector<MyGui::Info> vec_info)
	{
		Mark mark(label, pos);
		mark.GetBriefCase().name = name;
		mark.GetBriefCase().vec_info = vec_info;
		if (!filename.empty()) mark.GetBriefCase().image.SetupTexture(filename.c_str());
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

	void MarkContainer::ForAll(std::function<void(Mark&)> fn)
	{
		for (auto& m : m_marks) {
			fn(m);
		}
	}
	
}
