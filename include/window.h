#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <iostream>

struct WindowSpecifics {
	std::string title;
	int width = 800;
	int height = 600;

	bool resizable = true;
};

class Window
{
public:
	Window(const WindowSpecifics& specs = WindowSpecifics());
	~Window();
	void Create();
	void Destroy();
	void Update();

	glm::vec2 GetFrameBufferSize();
	bool ShouldClose() const;

	GLFWwindow* GetNativeWindow() const { return m_Handle; }

private:
	WindowSpecifics m_Specs;
	GLFWwindow* m_Handle = nullptr;
};

