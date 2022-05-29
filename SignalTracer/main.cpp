#include <iostream>

#include <assimp/BaseImporter.h>

#include "attenuation.hpp"
#include "importer.hpp"
#include "window.hpp"
#include "renderer.hpp"
#include "cutting_plane.hpp"
#include "heatmap.hpp"
#include "raycast.hpp"
#include "marker.hpp"

#include "logger.hpp"

const int width = 1280;
const int height = 768;

using namespace sgtr;

AccessPointsList make_ap_list() 
{
	AccessPoint p1;
	p1.signal_source_pos_ = math::Vector3f{ -65.0f, -70.0f, -20.001f };
	p1.freq_ = 5150;
	p1.y_ = 4;
	p1.power_ = 12;
	p1.gain_ = 5;
	p1.noise_ = 2;
	p1.cwidth_ = 40;
	p1.temperature_ = 300;
	p1.standard_ = ax;
	p1.map_type_ = SPEED;
	p1.scalefactor_ = 1.45f;

	AccessPoint p2;
	p2.signal_source_pos_ = math::Vector3f{ 0.0f, 0.0f, -20.001f };
	p2.freq_ = 5150;
	p2.y_ = 4;
	p2.power_ = 12;
	p2.gain_ = 5;
	p2.noise_ = 2;
	p2.cwidth_ = 40;
	p2.temperature_ = 300;
	p2.standard_ = ax;
	p2.map_type_ = SPEED;
	p2.scalefactor_ = 1.45f;

	return { p1, p2 };
}

int main(int argc, char** argv)
{
	try {
		auto cplane_x = 500.0f;
		auto cplane_y = 500.0f;
		unsigned res_x = 512;
		unsigned res_y = 512;
		auto access_points = make_ap_list();

		auto renderer = std::make_shared<Renderer>();
		auto plane = std::make_shared<ÑuttingPlane>(cplane_x, cplane_y);
		auto actions = std::make_shared<ActionsController>();
		auto window = std::make_shared<Window>(WindowDescriptor{ [renderer]() { renderer->render(width, height); }, 
												  			     [actions](UserAction act) { actions->onAction(act); }, 
															     width, 
																 height });

		auto importer = std::make_shared<Importer>("test_meshes\\plan0.fbx");
		auto model = importer->getGeometry();
		auto heatmap = std::make_shared<Heatmap>(res_x, res_y);
		auto attenuation = std::make_shared<Attenuation>(heatmap->getResolution());
		auto marker = std::make_shared<Marker>(access_points);
		auto raycast = std::make_shared<Raycast>(std::move(attenuation), model, heatmap, std::move(access_points), math::Vector2f{ cplane_x, cplane_y });

		plane->createPlane();
		actions->set(renderer, plane, std::move(raycast));
		renderer->init(std::move(model), std::move(plane), std::move(heatmap), std::move(marker));

		LOG(INFO) << "Entering display loop";
		return window->display();
	} catch (const std::exception& ex) {
		LOG(ERROR) << "Program ended with fatal exception: ";
		LOG(ERROR) << ex.what();
	}

	return -1;
}