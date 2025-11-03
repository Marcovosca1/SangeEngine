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
