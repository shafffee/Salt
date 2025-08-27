#pragma once
#include "Application.h"

extern salt::Application* CreateApplication();

int main(int argc, char** argv) {
	auto app = CreateApplication();
	app->defaultOnInit();
	app->defaultRun();
	app->defaultOnExit();
	delete(app);
	return 0;
};