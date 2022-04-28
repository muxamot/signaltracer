#include <iostream>

#include <assimp/BaseImporter.h>

#include "window.hpp"
#include "renderer.hpp"

#include "logger.hpp"

const int width = 1280; // ширина окна
const int height = 768; // высота окна

using namespace sgtr;

int main(int argc, char** argv)
{
	try {
		auto renderer = std::make_shared<Renderer>();
		auto actions = std::make_shared<ActionsController>(renderer);
		auto window = std::make_shared<Window>(sgtr::WindowDescriptor{ [renderer]() { renderer->render(width, height); }, 
																	   [actions](UserAction act) { actions->onAction(act); }, 
																	   width, 
																	   height });

		renderer->init();

		LOG(INFO) << "Entering display loop";
		return window->display();
	} catch (const std::exception& ex) {
		LOG(ERROR) << "Program ended with fatal exception: ";
		LOG(ERROR) << ex.what();
	}

	return -1;
}