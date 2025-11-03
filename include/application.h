#pragma once
#include "window.h"
#include <glm/glm.hpp>

#include <vector>
#include <string>
#include <memory>

struct AppSpecifics {
	std::string name = "SangeEngine";
	WindowSpecifics windowSpecs;
};

class Application
{
	public:
	Application(const AppSpecifics& specs = AppSpecifics());
	~Application();

	void Run();
	void Stop();

	glm::vec2 GetFrameBufferSize() const;

	static Application& Get();
	static float GetTime();

private:
	AppSpecifics m_Specs;
	std::shared_ptr<Window> m_Window;
	bool m_Running = false;
};

