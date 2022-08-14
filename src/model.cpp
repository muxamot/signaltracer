#include "model.hpp"

namespace sgtr
{

Model::Model(size_t size_hint)
{
    meshes_.reserve(size_hint);
    meshes_geometry_.reserve(size_hint);
}

void Model::add(sptr<IDrawable> drawable, GeometryData gdata)
{
    meshes_.emplace_back(std::move(drawable));
    meshes_geometry_.emplace_back(std::move(gdata));
}

drawable_vec_t& Model::getDrawableItems()
{
    return meshes_;
}

Model::gdata_list_t& Model::getGeometryItems()
{
    return meshes_geometry_;
}

} // namespace sgtr
