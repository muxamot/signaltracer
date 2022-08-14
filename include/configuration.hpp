#pragma once

#include "access_point.hpp"
#include "types.hpp"

#include <nlohmann/json.hpp>
#include <string_view>

namespace sgtr
{

class Configuration
{
private:
    sptr<ap_vec_t> list_;
    cplane_size_t cplane_size_{};
    heatmap_res_t heatmap_res_{};
    float scale_;

    float apParam(const nlohmann::json&, const std::string) const;
    AccessPoint parseAccessPoint(const nlohmann::json&);

public:
    explicit Configuration(std::string filename);
    ~Configuration() = default;

    sptr<ap_vec_t> getAPList() const noexcept;
    cplane_size_t getCuttingPlaneSize() const noexcept;
    heatmap_res_t getHeatmapResolution() const noexcept;
};

}; // namespace sgtr