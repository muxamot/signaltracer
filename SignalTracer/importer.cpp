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
		model_ = std::make_shared<Model>();
		model_->reserve(msize);

		const auto* root_node = scene->mRootNode;
		root_transform_matrix_ = root_node->mTransformation;

		std::generate_n(std::back_inserter(*model_), msize, [&, mnum = 0]() mutable {
			return generate_node(scene->mMeshes[mnum++]);
		});

		LOG(INFO) << "Imported " << msize << " meshes from model";
	}

	sptr<IDrawable> Importer::generate_node(const aiMesh* mesh)
	{
		using namespace math;

		std::vector<Vertex> vertices;
		std::vector<unsigned int> indexes;
	
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
			aiVector3t<float> rs = root_transform_matrix_ * aiVector3t<float>(vertex.m_pos.x, vertex.m_pos.y, vertex.m_pos.z);
			vertex.m_pos = Vector3f{ rs.x, rs.y, rs.z };
		}

		return std::make_shared<Mesh>(vertices, indexes);
	}

	sptr<Model> Importer::getGeometry()
	{
		return model_;
	}
}