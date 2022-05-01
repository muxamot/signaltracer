#include <assimp/Importer.hpp>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <assert.h>

#include "importer.hpp"
#include "logger.hpp"
#include "vertex.hpp"
#include "vector.hpp"
#include "mesh.hpp"
#include "model.hpp"

namespace sgtr
{
	Importer::Importer(const std::string& filename)
	{
		LOG(INFO) << "Import path = " << filename;
		LOG(INFO) << "Trying to import file (this may take some time......)";

		Assimp::Importer importer;
		const auto* scene = importer.ReadFile(filename.c_str(), 
			aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_OptimizeMeshes | aiProcess_OptimizeGraph | aiProcess_MakeLeftHanded);

		if (!scene) {
			LOG(ERROR) << "Failed to import model " << filename << " -- bad format or corrupted file!";
			LOG(ERROR) << "Importer says: " << importer.GetErrorString();
			throw std::exception("Failed to import model");
		}

		LOG(INFO) << "Loading geometry (this may take some time......)";

		const auto msize = scene->mNumMeshes;
		model_ = std::make_shared<Model>(msize);
		
		const auto* root_node = scene->mRootNode;
		root_transform_matrix_ = root_node->mTransformation;

		for (unsigned mnum = 0; mnum < msize; mnum++) {
			auto node = generate_node(scene->mMeshes[mnum++]);
			model_->add(std::move(node.first), std::move(node.second));
		}

		LOG(INFO) << "Imported " << msize << " meshes from model";
	}

	Importer::node_t Importer::generate_node(const aiMesh* mesh)
	{
		using namespace math;

		vertex_buf_t vertices;
		index_buf_t indexes;
	
		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			const aiVector3D* pPos = &(mesh->mVertices[i]);
			vertices.emplace_back(Vertex{ Vector3f{pPos->x, pPos->y, pPos->z }, Vector2f{ 0.0f, 0.0f } });
		}

		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			const auto& face = mesh->mFaces[i];
			
			assert(face.mNumIndices == 3);
			for(int j = 2; j >= 0; --j)
				indexes.push_back(face.mIndices[j]);
		}

		for (auto& vertex : vertices)
		{
			aiVector3t<float> rs = root_transform_matrix_ 
					* aiVector3t<float>(vertex.vertex_position_.x, vertex.vertex_position_.y, vertex.vertex_position_.z);
			vertex.vertex_position_ = Vector3f{ rs.x, rs.y, rs.z };
		}

		LOG(INFO) << "Mesh contains " << indexes.size() / 3 << " triangles";
		return std::make_pair(std::make_shared<Mesh>(vertices, indexes), GeometryData{ vertices, indexes });
	}

	sptr<Model> Importer::getGeometry()
	{
		return model_;
	}
}