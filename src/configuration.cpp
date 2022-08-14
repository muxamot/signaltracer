#include "configuration.hpp"

#include <fstream>
#include <nlohmann/json.hpp>

namespace sgtr
{

using json = nlohmann::json;

Configuration::Configuration(std::string filename)
    : list_(std::make_shared<ap_vec_t>())
{
    std::ifstream filestream{filename.data()};
    auto cfg = json::parse(filestream);

    if (!cfg.contains("signal_sources"))
        throw std::runtime_error{"Incorrect configuration file: there is no signal_sources node in json file"};

    scale_ = cfg["scale"].get<float>();

    for (auto& ap : cfg["signal_sources"])
        list_->emplace_back(parseAccessPoint(ap));

    auto cplane_size = cfg["cutting_plane_size"].get<float>();
    auto heatmap_res = cfg["heatmap_resolution"].get<uint32_t>();

    cplane_size_ = cplane_size_t{cplane_size, cplane_size};
    heatmap_res_ = heatmap_res_t{heatmap_res, heatmap_res};
}

float Configuration::apParam(const json& json, const std::string name) const
{
    if (!json.contains(name))
        throw std::runtime_error{"Incorrect configuration file: there is no key " + name + " in access point params"};

    return json[name].get<float>();
}

// some ugly boilerplate here
AccessPoint Configuration::parseAccessPoint(const json& ap)
{
    if (!ap.contains("position"))
        throw std::runtime_error{"Incorrect configuration file: no access point position"};

    const auto& pos = ap["position"];

    AccessPoint p;
    p.signal_source_pos_ = math::Vector3f{pos["x"].get<float>(), pos["y"].get<float>(), pos["z"].get<float>()};
    p.freq_ = apParam(ap, "frequency");
    p.y_ = apParam(ap, "attenuation");
    p.power_ = apParam(ap, "power");
    p.gain_ = apParam(ap, "gain");
    p.noise_ = apParam(ap, "noise");
    p.cwidth_ = apParam(ap, "channel_width");
    p.temperature_ = apParam(ap, "temperature");
    p.standard_ = (ap["standard"].get<std::string>() == std::string{"ax"}) ? ax : ac;
    p.map_type_ = SPEED;
    p.scalefactor_ = scale_;

    return p;
}

sptr<ap_vec_t> Configuration::getAPList() const noexcept
{
    return list_;
}

cplane_size_t Configuration::getCuttingPlaneSize() const noexcept
{
    return cplane_size_;
}

heatmap_res_t Configuration::getHeatmapResolution() const noexcept
{
    return heatmap_res_;
}

} // namespace sgtr