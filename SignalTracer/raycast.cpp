#include <algorithm>
#include <glm/glm.hpp>

#include "raycast.hpp"

using namespace glm;

static inline glm::vec3 toGLM(const math::Vector3f vect) 
{
	return vec3(vect.x, vect.y, vect.z);
}

namespace sgtr {
	
	Raycast::Raycast(sptr<Model> model, sptr<Heatmap> heatmap, math::Vector3f signal_source, math::Vector2f cplane_size)
		: model_(std::move(model))
		, heatmap_(std::move(heatmap))
		, source_(signal_source)
		, cplane_size_(cplane_size)
	{
		resolution_ = heatmap_->getResolution();
		threads_count_ = std::thread::hardware_concurrency();
		LOG(INFO) << "Threads used for computation = " << threads_count_;
	}

	// Moller-Trumbore intersection detection algorithm
	float Raycast::ray_intersection(const math::Vector3f& origin, const math::Vector3f& direction, 
		const math::Vector3f& vertex0, const math::Vector3f& vertex1, const math::Vector3f& vertex2) const
	{
		auto orig = toGLM(origin);
		auto dir = toGLM(direction);
		auto v0 = toGLM(vertex0);
		auto v1 = toGLM(vertex1);
		auto v2 = toGLM(vertex2);

		vec3 e1 = v1 - v0;
		vec3 e2 = v2 - v0;
		
		// normal to plane
		vec3 pvec = cross(dir, e2);
		float det = dot(e1, pvec);

		// parallel case
		if (det < 1e-8 && det > -1e-8) {
			return 0;
		}

		const float inv_det = 1.0f / det;
		vec3 tvec = orig - v0;
		const float u = dot(tvec, pvec) * inv_det;

		if (u < 0.0f || u > 1.0f)
			return 0;

		vec3 qvec = cross(tvec, e1);
		const float v = dot(dir, qvec) * inv_det;
		if (v < 0.0f || u + v > 1.0f)
			return 0;

		const float f = dot(e2, qvec) * inv_det;
		if (f > DETECTION_PRECISION) {
			const auto point = (orig + dir * f);
			return glm::length(point - orig);
		} else {
			return 0;
		}
	}

	void Raycast::iterateGeometry(geometry_iter_cb_t callback)
	{
		for (auto& geometry : model_->getGeometryItems())
		{
			if (geometry.index_buffer_.size() % 3 != 0)
			{
				LOG(ERROR) << "Mesh geometry index buffer is invalid, aborting";
				throw std::exception("Index buffer is invalid");
			}

			for (unsigned i = 0; i < geometry.index_buffer_.size(); i += 3)
			{
				if (!callback(std::make_tuple(&geometry.vertex_buffer_.at(geometry.index_buffer_.at(i))
					, &geometry.vertex_buffer_.at(geometry.index_buffer_.at(i + 1))  
					, &geometry.vertex_buffer_.at(geometry.index_buffer_.at(i + 2)))))
					return;
			}
		}
	}

	math::Vector2f Raycast::fromMapToPlaneSpace(const math::Vector2ui& point) const
	{
		const auto normalized_x = point.x / static_cast<float>(resolution_.x);
		const auto normalized_y = point.y / static_cast<float>(resolution_.y);

		return math::Vector2f{ (normalized_y * cplane_size_.y) - (cplane_size_.y / 2.0f),
			-1 * ((normalized_x * cplane_size_.x) - (cplane_size_.x / 2.0f)) };
	}

	float Raycast::getMapPointValue(math::Vector2ui point)
	{
		std::vector<float> hits;
		bool wall{ false };
		float score{ 1.0f };

		auto ps_point = fromMapToPlaneSpace(std::move(point));
		math::Vector3f destination = math::Vector3f{ ps_point.x, ps_point.y, offset_ };
		
		float proj_distance = std::sqrt(std::powf(destination.x - source_.x, 2.0f)
			+ std::powf(destination.y - source_.y, 2.0f) + std::powf(destination.z - source_.z, 2.0f));

		for(const auto& triangle : filtered_triangles_) {
			float dist = ray_intersection(source_, destination, std::get<0>(triangle)->vertex_position_, 
				std::get<1>(triangle)->vertex_position_, std::get<2>(triangle)->vertex_position_);

			if (dist > DETECTION_PRECISION && dist < proj_distance)
				hits.push_back(dist);
		}

		std::sort(hits.begin(), hits.end());

		for (const auto& value : hits)
		{
			score -= 0.1f;
			wall = !wall; //flip
		}

		return score;
	}

	void Raycast::updateMap(float offset)
	{
		offset_ = offset;
		filtered_triangles_.clear();

		// drop unreachable triangles
		iterateGeometry([&](triangle_vxset_t v) -> bool {
			if (std::get<0>(v)->vertex_position_.z > offset_ || std::get<1>(v)->vertex_position_.z > offset_ 
						|| std::get<2>(v)->vertex_position_.z > offset_)
				filtered_triangles_.push_back(v);
			return true;
		});

		auto stripe = resolution_.x / threads_count_;

		threads_.clear();
		for (unsigned i = 0; i < threads_count_; i++) {
			threads_.emplace_back([this, stripe, thread_num = i]() {
				for (unsigned x = thread_num*stripe; x < ((thread_num*stripe)+stripe); x++)
				{
					for (unsigned y = 0; y < resolution_.y; y++)
					{
						heatmap_->setLevelAt(getMapPointValue({ x, y }), x, y);
					}
				}
			});
		}
		
		for (auto& t : threads_)
			if (t.joinable())
				t.join();

		heatmap_->applyChanges();
	}
}
