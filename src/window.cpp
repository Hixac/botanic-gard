#include <window.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <marble.hpp>

#include <cassert>

namespace Window {

	Window::Window(std::string name, int width, int height)
		: m_name(name)
	{
		Window::Window::SetHeight(height);
		Window::Window::SetWidth(width);

		if (!glfwInit()) { // Может быть проблема с зависимостями
			assert(false && "GLFW INITIALIZATION WENT WRONG BRUV");
		}
		glfwSetErrorCallback(Window::ErrorCallBack);
		
		m_pwindow = glfwCreateWindow(ms_width, ms_height, name.c_str(), NULL, NULL);
		if (!m_pwindow) { // Окно не создалось
			glfwTerminate();
		}

		// Сделать окно видимым поверх всех
		glfwMakeContextCurrent(m_pwindow);
		glfwSwapInterval(1); // vsync
		glfwSetWindowSizeLimits(m_pwindow, 500, 300, GLFW_DONT_CARE, GLFW_DONT_CARE);

		glfwSetMouseButtonCallback(m_pwindow, Window::ButtonCallBack);
		glfwSetCursorPosCallback(m_pwindow, Window::MousePosCallBack);
		
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controlss

		io.Fonts->AddFontFromFileTTF("JetBrainsMonoNLNerdFontMono-Regular.ttf", 23, nullptr, io.Fonts->GetGlyphRangesCyrillic());
		
		ImGui::StyleColorsDark();
	    ImGui_ImplGlfw_InitForOpenGL(m_pwindow, true);
		ImGui_ImplOpenGL3_Init(nullptr);
	}

	Window::~Window()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		glfwDestroyWindow(m_pwindow);
		glfwTerminate();
	}

    void Window::OnUpdateCallBack(std::function<void()> mainupdatefn)
	{
	    while (!glfwWindowShouldClose(m_pwindow))
		{
			glfwPollEvents();
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			mainupdatefn();
			
			for (const auto& fn : updatefns) {
				fn();
			}
			
		    glClear(GL_COLOR_BUFFER_BIT);
			
			ImGui::Render();
			glfwGetFramebufferSize(m_pwindow, &ms_width, &ms_height);
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(m_pwindow);

			// CLEAR STUFF
			ms_leftmousedown = false;
		}
	}

	void Window::ErrorCallBack(int code, const char* descr)
	{
		assert(false && descr && "code is" && code);
	}
	
	void Window::ButtonCallBack(GLFWwindow* window, int button, int action, int mods)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
			ms_leftmousedown = true;
		}
	}
	
	void Window::MousePosCallBack(GLFWwindow* window, double xpos, double ypos)
	{
		m_xpos = xpos; m_ypos = ypos;
	}
}
