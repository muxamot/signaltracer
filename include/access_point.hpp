#pragma once

#include "vector.hpp"
#include <vector>


namespace sgtr
{
enum Type
{
    ac,
    ax
};

enum MapType
{
    SPEED,
    ATTEN
};

struct AccessPoint
{
    math::Vector3f signal_source_pos_;

    float freq_;
    float y_;
    float power_;
    float gain_;
    float gain_rcv_;
    float noise_;
    float cwidth_;
    float temperature_;
    float scalefactor_;
    Type standard_;
    MapType map_type_;
};

using AccessPointsList = std::vector<AccessPoint>;
} // namespace sgtr