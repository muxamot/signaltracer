#include <iostream>

#include <assimp/BaseImporter.h>

#include "importer.hpp"
#include "window.hpp"
#include "renderer.hpp"
#include "cutting_plane.hpp"
#include "heatmap.hpp"
#include "raycast.hpp"

#include "logger.hpp"

const int width = 1280;
const int height = 768;

using namespace sgtr;

int main(int argc, char** argv)
{
	try {
		auto cplane_x = 48.0f;
		auto cplane_y = 48.0f;

		auto renderer = std::make_shared<Renderer>();
		auto plane = std::make_shared<ÑuttingPlane>(cplane_x, cplane_y);
		auto actions = std::make_shared<ActionsController>();
		auto window = std::make_shared<Window>(WindowDescriptor{ [renderer]() { renderer->render(width, height); }, 
												  			     [actions](UserAction act) { actions->onAction(act); }, 
															     width, 
																 height });

		auto importer = std::make_shared<Importer>("test_meshes\\exported_2013.fbx");
		auto model = importer->getGeometry();
		auto heatmap = std::make_shared<Heatmap>(256, 256);
		auto raycast = std::make_shared<Raycast>(model, heatmap, math::Vector3f{ 0.0f, 0.0f, 6.0f }, math::Vector2f{ cplane_x, cplane_y });

		plane->createPlane();

		actions->set(renderer, plane, std::move(raycast));
		renderer->init(std::move(model), std::move(plane), std::move(heatmap));

		LOG(INFO) << "Entering display loop";
		return window->display();
	} catch (const std::exception& ex) {
		LOG(ERROR) << "Program ended with fatal exception: ";
		LOG(ERROR) << ex.what();
	}

	return -1;
}