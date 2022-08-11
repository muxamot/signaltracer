#pragma once

#include "access_point.hpp"
#include "attenuation.hpp"
#include "heatmap.hpp"
#include "model.hpp"

#include <functional>
#include <list>
#include <thread>
#include <tuple>

namespace sgtr
{
class Raycast
{
private:
    using triangle_vxset_t = std::tuple<math::Vertex*, math::Vertex*, math::Vertex*>;
    using triangle_list_t = std::list<triangle_vxset_t>;
    using geometry_iter_cb_t = std::function<bool(triangle_vxset_t)>;

    constexpr static auto DETECTION_PRECISION = 0.0001f;

    triangle_list_t filtered_triangles_;
    std::vector<std::thread> threads_;
    size_t threads_count_{16};

    // math::Vector3f source_;
    AccessPointsList ap_list_;
    math::Vector2f cplane_size_;
    math::Vector2ui resolution_;

    sptr<Attenuation> attenuation_;
    sptr<Model> model_;
    sptr<Heatmap> heatmap_;
    float offset_;

    float ray_intersection(const math::Vector3f&, const math::Vector3f&, const math::Vector3f&, const math::Vector3f&,
                           const math::Vector3f&) const;

    void iterateGeometry(geometry_iter_cb_t);
    math::Vector2f fromMapToPlaneSpace(const math::Vector2ui&) const;
    void cast(const math::Vector2ui&, const math::Vector3f&);
    void updateHeatmap();

public:
    Raycast(sptr<Attenuation>, sptr<Model>, sptr<Heatmap>, AccessPointsList, math::Vector2f);
    ~Raycast() = default;

    void updateMap(float offset);
};

} // namespace sgtr