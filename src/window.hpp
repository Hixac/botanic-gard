#pragma once

#include <string>
#include <functional>

#include <glfw3.h>

namespace Window {

	class Window
	{
	public:
		Window(std::string name, int width, int height);
		~Window();

	    void OnUpdateCallBack(std::function<void()> fn);

	private:
		static void ErrorCallBack(int code, const char* descr);
		
		GLFWwindow* m_pwindow;
		
		std::string m_name;
		int m_height;
		int m_width;
	};	
}
