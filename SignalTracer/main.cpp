#include <iostream>

#include <assimp/BaseImporter.h>

#include "window.hpp"
#include "renderer.hpp"

#include "logger.hpp"

const int width = 1280; // ширина окна
const int height = 768; // высота окна

int main(int argc, char** argv)
{
	try {
		auto renderer = std::make_shared<sgtr::Renderer>();
		auto window = std::make_shared<sgtr::Window>(sgtr::WindowDescriptor{ [r = renderer]() { r->render(width, height); }, [&](sgtr::UserAction action) {}, width, height });
		renderer->init();

		return window->display();
	} catch (const std::exception& ex) {
		sgtr::LOG(sgtr::ERROR) << "Program ended with fatal exception: ";
		sgtr::LOG(sgtr::ERROR) << ex.what();
	}

	return -1;
}