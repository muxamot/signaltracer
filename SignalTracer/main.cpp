#include <iostream>

#include <assimp/BaseImporter.h>

#include "importer.hpp"
#include "window.hpp"
#include "renderer.hpp"
#include "cutting_plane.hpp"

#include "logger.hpp"

const int width = 1280; // ширина окна
const int height = 768; // высота окна

using namespace sgtr;

int main(int argc, char** argv)
{
	try {
		auto renderer = std::make_shared<Renderer>();
		auto actions = std::make_shared<ActionsController>(renderer);
		auto window = std::make_shared<Window>(WindowDescriptor{ [renderer]() { renderer->render(width, height); }, 
												  			     [actions](UserAction act) { actions->onAction(act); }, 
															     width, 
																 height });

		auto importer = std::make_shared<Importer>("test_meshes\\house.fbx");

		renderer->init(importer->getGeometry(), std::make_shared<СuttingPlane>(9.99f, 9.99f));

		LOG(INFO) << "Entering display loop";
		return window->display();
	} catch (const std::exception& ex) {
		LOG(ERROR) << "Program ended with fatal exception: ";
		LOG(ERROR) << ex.what();
	}

	return -1;
}