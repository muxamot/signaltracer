#include <algorithm>
#include <vector>

#include "marker.hpp"
#include "vertex.hpp"

namespace sgtr
{	
	void Marker::createVB(const AccessPointsList& ap_list)
	{
		using namespace math;
		std::vector<Vertex> vertex;
		vertex.reserve(VERTEX_BY_MARKER_COUNT_ * ap_list.size());

		std::for_each(ap_list.begin(), ap_list.end(), [&](const AccessPoint& ap) {
			const auto& pos = ap.signal_source_pos_;
			vertex.push_back(Vertex{ pos + Vector3f{ 0.0f, 0.0f, 2.f}, Vector2f{} });
			vertex.push_back(Vertex{ pos + Vector3f{ -2.f, -2.f, -2.f}, Vector2f{} });
			vertex.push_back(Vertex{ pos + Vector3f{ 2.f, -2.f, -2.f }, Vector2f{} });
			vertex.push_back(Vertex{ pos + Vector3f{ 2.f, 2.f,  -2.f }, Vector2f{} });
			vertex.push_back(Vertex{ pos + Vector3f{ -2.f, 2.f,  -2.f }, Vector2f{} });
		});
		
		glGenBuffers(1, &vb_);
		glBindBuffer(GL_ARRAY_BUFFER, vb_);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertex.size(), vertex.data(), GL_STATIC_DRAW);
	}

	size_t Marker::createIB(size_t ap_count)
	{
		std::vector<unsigned int> index;
		index.reserve(INDEX_BY_MARKER_COUNT_ * ap_count);

		const std::vector<unsigned int> marker_idx{
				0, 1, 2,
				0, 1, 4,
				0, 4, 3,
				0, 3, 2,
				1, 4, 2,
				4, 2, 3
		};

		for(unsigned n = 0; n < ap_count; n++){
			unsigned int offset = n * VERTEX_BY_MARKER_COUNT_;
			
			std::for_each(marker_idx.begin(), marker_idx.end(), [&](unsigned int idx) {
				index.push_back(offset + idx);
			});
		}

		glGenBuffers(1, &ib_);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * index.size(), index.data(), GL_STATIC_DRAW);

		return index.size();
	}

	Marker::Marker(const AccessPointsList& ap_list)
	{
		idx_count_ = createIB(ap_list.size());
		createVB(std::move(ap_list));
	}

	size_t Marker::getIndexCount() const
	{
		return idx_count_;
	}

	GLuint Marker::getIndexBuffer() const
	{
		return ib_;
	}

	GLuint Marker::getVertexBuffer() const
	{
		return vb_;
	}

}
