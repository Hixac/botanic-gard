#pragma once

#include <string>
#include <functional>
#include <vector>

#include <glfw3.h>
#include <imgui.h>

namespace Window {

	class Window
	{
	public:
		Window(std::string name, int width, int height);
		~Window();

	    void OnUpdateCallBack(std::function<void()> mainupdatefn);

		inline int GetWidth()  { return m_width;  } 
		inline int GetHeight() { return m_height; }

		ImVec2 GetVec() { return {static_cast<float>(m_width), static_cast<float>(m_height)}; }
		
		std::vector<std::function<void()>> updatefns;
	private:
		static void ErrorCallBack(int code, const char* descr);
		
		GLFWwindow* m_pwindow;
		
		std::string m_name;
		int m_height;
		int m_width;
	};	
}
