#include <iostream>

#include <assimp/BaseImporter.h>

#include "attenuation.hpp"
#include "configuration.hpp"
#include "cutting_plane.hpp"
#include "heatmap.hpp"
#include "importer.hpp"
#include "marker.hpp"
#include "raycast.hpp"
#include "renderer.hpp"
#include "window.hpp"

#include "logger.hpp"

const int width = 1280;
const int height = 768;

using namespace sgtr;

int main(int argc, const char** argv)
{
    try
    {
        std::string model_fname;
        std::string config_fname;

        // clang-format off
        if (argc == 1) {
            LOG(INFO) << "No filnames provided in args, using some test defaults";
            model_fname = "plan.fbx";
            config_fname = "plan-params.json";
        } else if (argc == 3) {
            model_fname = std::string{argv[1]};
            config_fname = std::string{argv[2]};
        } else {
            throw std::runtime_error{"Invalid args count. Usage: ./sigtracer <MODEL> <CONFIG>"};
        }
        // clang-format on

        auto config = Configuration{config_fname};

        auto renderer = std::make_shared<Renderer>();
        auto plane = std::make_shared<CuttingPlane>(config.getCuttingPlaneSize());
        auto actions = std::make_shared<ActionsController>();
        auto window = std::make_shared<Window>(WindowDescriptor{[renderer]() { renderer->render(width, height); },
                                                                [actions](UserAction act) { actions->onAction(act); },
                                                                width, height});

        auto importer = std::make_shared<Importer>(model_fname);
        auto model = importer->getGeometry();
        auto heatmap = std::make_shared<Heatmap>(config.getHeatmapResolution());
        auto attenuation = std::make_shared<Attenuation>(heatmap->getResolution());
        auto marker = std::make_shared<Marker>(config.getAPList());
        auto raycast = std::make_shared<Raycast>(std::move(attenuation), model, heatmap, config.getAPList(),
                                                 config.getCuttingPlaneSize());

        plane->createPlane();
        actions->set(renderer, plane, std::move(raycast));
        renderer->init(std::move(model), std::move(plane), std::move(heatmap), std::move(marker));

        LOG(INFO) << "Entering display loop";
        return window->display();
    }
    catch (const std::exception& ex)
    {
        LOG(ERROR) << "Program ended with fatal exception: ";
        LOG(ERROR) << ex.what();
    }

    return -1;
}