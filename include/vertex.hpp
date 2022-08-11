#pragma once

#include "vector.hpp"

namespace math
{

struct Vertex
{
    Vector3f vertex_position_;
    Vector2f texture_postition_;

    Vertex() = default;
    explicit Vertex(Vector3f pos, Vector2f tex)
        : vertex_position_(pos)
        , texture_postition_(tex)
    {
    }
};

} // namespace math