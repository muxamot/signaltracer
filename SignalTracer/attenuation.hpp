#pragma once

#include <array>
#include <vector>

#include "vector.hpp"
#include "access_point.hpp"
#include "stats.hpp"

namespace sgtr
{
	class Attenuation
	{
	private:
		using hits_vec_t = std::vector<float>;
		using att_map_t = std::vector<std::vector<float>>;

		constexpr static double k = 1.38e-23;
		constexpr static std::array<float, 12> SRS1 = { 30.f, 60.f, 90.f, 120.f, 180.f, 240.f, 270.f, 300.f, 360.f, 400.f };
		constexpr static std::array<float, 12> SRS2 = { 34.4f, 68.f, 104.f, 138.f, 206.f, 276.f, 310.f, 344.f, 414.f, 458.f, 516.f, 574.f};
		constexpr static std::array<float, 12> SNRSR1 = { 18.f, 21.f, 23.f, 28.f, 32.f, 37.f, 39.f, 41.f, 47.f, 50.f };
		constexpr static std::array<float, 12> SNRSR2 = { 15.f, 18.f, 21.f, 28.f, 31.f, 33.f, 40.f, 45.f, 49.f, 53.f, 55.f, 57.f };

		att_map_t map_;
		math::Vector2ui resolution_;
		AccessPoint params_;
		Stats<unsigned> stats_;

		struct radio_att {
			float l_air_;
			float l_crt_;
			float l_total_;
		};

		radio_att getAttenuation(float, float);
		float getSNR(float, float, float);
		float getSpeed(float);
		void mapAllocate();

	public:
		Attenuation(math::Vector2ui);

		void clear();
		void setParams(const AccessPoint&);
		void addHitsVector(math::Vector2ui, float, hits_vec_t);
		void statsPrint();
		void normalize();
		float getNormalizedAttenuationValue(math::Vector2ui) const noexcept;
	};

}