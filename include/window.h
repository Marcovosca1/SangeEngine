#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <iostream>
#include <vector>

#include "inputSystem.h"

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

	void RegisterObserver(InputSystem& observer);
	void RemoveObserver(InputSystem& observer);

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouseClick_callback(GLFWwindow* window, int button, int action, int mods);
	static void mouseMove_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

private:
	//std::vector<InputSystem> m_Observers;
	WindowSpecifics m_Specs;
	GLFWwindow* m_Handle = nullptr;
};

