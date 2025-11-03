#include "application.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <assert.h>
#include <iostream>

static Application* s_Instance = nullptr;

Application::Application(const AppSpecifics& specs)
	: m_Specs(specs)
{
	s_Instance = this;

	glfwInit();
	if(m_Specs.windowSpecs.title.empty())
		m_Specs.windowSpecs.title = m_Specs.name;

	m_Window = std::make_shared<Window>(m_Specs.windowSpecs);
	m_Window->Create();
}

Application::~Application()
{
	m_Window->Destroy();
	glfwTerminate();
	s_Instance = nullptr;
}

void Application::Run()
{
	m_Running = true;
	float lastTime = GetTime();

	while (m_Running)
	{
		glfwPollEvents();

		if (m_Window->ShouldClose()) {
			Stop();
			break;
		}

		float currentTime = GetTime();
		float deltaTime = glm::clamp(currentTime - lastTime, 0.001f, 0.01f);
		lastTime = currentTime;

		m_Window->Update();
	}
}

void Application::Stop()
{
	m_Running = false;
}

glm::vec2 Application::GetFrameBufferSize() const
{
	return m_Window->GetFrameBufferSize();
}

Application& Application::Get()
{
	assert(s_Instance && "Application instance does not exist!");
	return *s_Instance;
}

float Application::GetTime()
{
	return (float)glfwGetTime();
}
