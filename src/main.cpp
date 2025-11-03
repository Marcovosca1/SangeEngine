#include "application.h"

int main()
{
	AppSpecifics appSpecs;
	appSpecs.name = "Sange Engine";
	appSpecs.windowSpecs.width = 1920;
	appSpecs.windowSpecs.height = 1080;

	Application app(appSpecs);
	app.Run();
}