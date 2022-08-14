#pragma once

#include "types.hpp"

namespace sgtr
{

struct GeometryData
{
    vertex_buf_t vertex_buffer_;
    index_buf_t index_buffer_;
};

class Model
{
private:
    using gdata_list_t = std::vector<GeometryData>;

    drawable_vec_t meshes_;
    gdata_list_t meshes_geometry_;

public:
    Model(size_t size_hint = 1);

    void add(sptr<IDrawable>, GeometryData);
    drawable_vec_t& getDrawableItems();
    gdata_list_t& getGeometryItems();
};

} // namespace sgtr