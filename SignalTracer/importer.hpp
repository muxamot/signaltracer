#pragma once

#include <string>
#include <assimp/matrix4x4.h>
#include <assimp/mesh.h>

#include "drawable_interface.hpp"
#include "types.hpp"

namespace sgtr 
{	
	class Importer
	{
	private:
		sptr<Model> model_;
		size_t transfrom_count_{0};
		aiMatrix4x4 root_transform_matrix_;

		sptr<IDrawable> generate_node(const aiMesh*);

	public:
		Importer(const std::string&);
		sptr<Model> getGeometry();
	};
}