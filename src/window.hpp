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

		inline static ImVec2 GetMousePosition() { return {static_cast<float>(ms_xpos), static_cast<float>(ms_ypos)}; }
		
		inline static bool GetLeftMousePress() { return ms_leftmousepress; }
		inline static bool GetRightMousePress() { return ms_rightmousepress; }
		inline static bool GetLeftMouseAbsPress() { return ms_leftmouseabspress; }
		inline static bool GetRightMouseAbsPress() { return ms_rightmouseabspress; }
		inline static bool GetLeftMouseRelease() { return ms_leftmouserelease; }
		inline static bool GetRightMouseRelease() { return ms_rightmouserelease; }
		inline static bool GetLeftMouseAbsRelease() { return ms_leftmouserelease; }
		inline static bool GetRightMouseAbsRelease() { return ms_rightmouserelease; }
		
	private:

		inline static void SetHeight(int height) { ms_height = height; }
		inline static void SetWidth(int width) { ms_width = width; }
		
		static void ErrorCallBack(int code, const char* descr);
		static void ButtonCallBack(GLFWwindow* window, int button, int action, int mods);
		static void MousePosCallBack(GLFWwindow* window, double xpos, double ypos);
		
		inline static bool ms_leftmousepress = false;
		inline static bool ms_rightmousepress = false;
		inline static bool ms_leftmouseabspress = false;
		inline static bool ms_rightmouseabspress = false;
		inline static bool ms_leftmouserelease = false;
		inline static bool ms_rightmouserelease = false;
		inline static bool ms_leftmouseabsrelease = false;
		inline static bool ms_rightmouseabsrelease = false;
		inline static double ms_xpos, ms_ypos;
		
		GLFWwindow* m_pwindow;
		
		std::string m_name;
		inline static int ms_height = 0;
		inline static int ms_width = 0;
	};	
}
