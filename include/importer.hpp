#pragma once

#include <assimp/matrix4x4.h>
#include <assimp/mesh.h>
#include <string>

#include "drawable_interface.hpp"
#include "model.hpp"
#include "types.hpp"

namespace sgtr
{

class Importer
{
private:
    using node_t = std::pair<sptr<IDrawable>, GeometryData>;

    sptr<Model> model_;
    size_t transfrom_count_{0};
    aiMatrix4x4 root_transform_matrix_;

    node_t generate_node(const aiMesh*);

public:
    Importer(const std::string&);
    sptr<Model> getGeometry();
};

} // namespace sgtr