#include "window.h"

Window::Window(const WindowSpecifics& specs)
	: m_Specs(specs)
{
}

Window::~Window()
{
	Destroy();
}

void Window::Create()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (!m_Specs.resizable)
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	m_Handle = glfwCreateWindow(m_Specs.width, m_Specs.height, m_Specs.title.c_str(), nullptr, nullptr);

	if(!m_Handle)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_Handle);
	glfwSetKeyCallback(m_Handle, Window::key_callback);

}

void Window::Destroy()
{
	if (m_Handle)
	{
		glfwDestroyWindow(m_Handle);
	}
	m_Handle = nullptr;
}

void Window::Update()
{
	glfwSwapBuffers(m_Handle);
}

glm::vec2 Window::GetFrameBufferSize()
{
	int width, height;
	glfwGetFramebufferSize(m_Handle, &width, &height);
	return { width, height };
}

bool Window::ShouldClose() const
{
	return glfwWindowShouldClose(m_Handle) != 0;
}

void Window::RegisterObserver(InputSystem& observer)
{
	//m_Observers.push_back(observer);
}

void Window::RemoveObserver(InputSystem& observer)
{
	//m_Observers.erase(std::remove(m_Observers.begin(), m_Observers.end(), observer), m_Observers.end());
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	
}

void Window::mouseClick_callback(GLFWwindow* window, int button, int action, int mods)
{
}

void Window::mouseMove_callback(GLFWwindow* window, double xpos, double ypos)
{
}

void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
}
