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

		inline static int GetWidth()  { return ms_width;  } 
		inline static int GetHeight() { return ms_height; }

		inline static ImVec2 GetVec() { return {static_cast<float>(ms_width), static_cast<float>(ms_height)}; }
		
		std::vector<std::function<void()>> updatefns;

		inline static ImVec2 GetMousePosition() { return {static_cast<float>(m_xpos), static_cast<float>(m_ypos)}; }
		inline static bool GetLeftMouseDown() { return ms_leftmousedown; }
	private:

		inline static void SetHeight(int height) { ms_height = height; }
		inline static void SetWidth(int width) { ms_width = width; }
		
		static void ErrorCallBack(int code, const char* descr);
		static void ButtonCallBack(GLFWwindow* window, int button, int action, int mods);
		static void MousePosCallBack(GLFWwindow* window, double xpos, double ypos);
		
		inline static bool ms_leftmousedown = false;
		inline static double m_xpos, m_ypos;
		
		GLFWwindow* m_pwindow;
		
		std::string m_name;
		inline static int ms_height = 0;
		inline static int ms_width = 0;
	};	
}
