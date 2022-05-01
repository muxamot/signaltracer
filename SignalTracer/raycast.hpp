#pragma once

#include <thread>

#include "heatmap.hpp"
#include "model.hpp"

namespace sgtr
{
	class Raycast
	{
	private:
		constexpr static auto DETECTION_PRECISION = 0.001f;

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

		math::Vector2f fromMapToPlaneSpace(const math::Vector2ui&) const;
		float getMapPointValue(math::Vector2ui);

	public:
		Raycast(sptr<Model>, sptr<Heatmap>, math::Vector3f, math::Vector2f);
		~Raycast() = default;

		void updateMap(float offset);
	};

}