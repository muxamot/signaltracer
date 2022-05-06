#pragma once

#include <thread>
#include <list>
#include <tuple>

#include "heatmap.hpp"
#include "model.hpp"

namespace sgtr
{
	class Raycast
	{
	private:
		using triangle_vxset_t = std::tuple<math::Vertex*, math::Vertex*, math::Vertex*>;
		using triangle_list_t = std::list<triangle_vxset_t>;
		using geometry_iter_cb_t = std::function<bool(triangle_vxset_t)>;
		
		constexpr static auto DETECTION_PRECISION = 0.001f;

		triangle_list_t filtered_triangles_;
		std::vector<std::thread> threads_;
		size_t threads_count_{16};

		math::Vector3f source_;
		math::Vector2f cplane_size_;
		math::Vector2ui resolution_;
		sptr<Model> model_;
		sptr<Heatmap> heatmap_;
		float offset_;

		float ray_intersection(const math::Vector3f&,
							   const math::Vector3f&,
							   const math::Vector3f&,
							   const math::Vector3f&,
							   const math::Vector3f&
		) const;

		void iterateGeometry(geometry_iter_cb_t);
		math::Vector2f fromMapToPlaneSpace(const math::Vector2ui&) const;
		float getMapPointValue(math::Vector2ui);

	public:
		Raycast(sptr<Model>, sptr<Heatmap>, math::Vector3f, math::Vector2f);
		~Raycast() = default;

		void updateMap(float offset);
	};

}