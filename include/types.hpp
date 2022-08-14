#pragma once

#include <memory>
#include <vector>

#include "access_point.hpp"
#include "drawable_interface.hpp"
#include "vertex.hpp"

namespace sgtr
{

template <typename T>
using sptr = std::shared_ptr<T>;

template <typename T>
using uptr = std::unique_ptr<T>;

template <typename T>
using wptr = std::weak_ptr<T>;

using vertex_buf_t = std::vector<math::Vertex>;
using index_buf_t = std::vector<unsigned int>;
using drawable_vec_t = std::vector<sptr<IDrawable>>;
using ap_vec_t = std::vector<AccessPoint>;

template <typename T>
struct Resolution
{
    T x_;
    T y_;
};

using cplane_size_t = Resolution<float>;
using heatmap_res_t = Resolution<uint32_t>;

} // namespace sgtr