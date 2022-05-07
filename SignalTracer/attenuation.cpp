#include <algorithm>

#include "attenuation.hpp"

namespace sgtr
{
	Attenuation::Attenuation(math::Vector2ui resolution, AccessPointParams params)
		: params_(params)
	{
		map_.resize(resolution.x);
		for (auto& row : map_)
			row.resize(resolution.y, 0.0f);
	}

	Attenuation::radio_att Attenuation::getAttenuation(float rair, float rcrt)
	{
		const auto l_air = 32.4f + 20 * std::log10f(params_.freq_ * 100) + 20 * std::log10f(rair / 1000.0f);
		const auto l_crt = params_.y_ * rcrt;
		return radio_att{
			l_air,
			l_crt,
			l_air + l_crt
		};
	}

	float Attenuation::getSNR(float distance, float rair, float rcrt)
	{
		return (params_.power_ + params_.gain_ - (getAttenuation(rair, rcrt).l_total_ / params_.scalefactor_)  - params_.noise_ 
			- 10 * std::log10(k * params_.temperature_ * params_.cwidth_) - 90.0);
	}

	float Attenuation::getSpeed(float SNR)
	{
		auto p = (params_.standard_ == ac) ? 10U : 12U;
		auto& SRS = (params_.standard_ == ac) ? SRS1 : SRS2;
		auto& SNRSR = (params_.standard_ == ac) ? SNRSR1 : SNRSR2;
	
		float spd{ 0.0f };

		for (unsigned i = 1; i < p; i++)
		{
			spd += (SNR < SNRSR.at(i)) ? 0 :  SRS.at(i) - SRS.at(i - 1);
		}

		return spd;
	}

	void Attenuation::addHitsVector(math::Vector2ui point, float distance, hits_vec_t hits)
	{
		bool wall{ false };
		hits.push_back(distance);
		std::sort(hits.begin(), hits.end());

		float last = 0.0f;

		float rair = 0.0f;
		float rcrt = 0.0f;

		for (const auto& value : hits)
		{
			float segment = value - last;

			if (wall)
				rcrt += segment;
			else
				rair += segment;

			wall = !wall; //flip
			last = value;
		}

		if (params_.map_type_ == ATTEN) {
			const auto att = getAttenuation(rair, rcrt);
			map_.at(point.x).at(point.y) = att.l_total_;
			return;
		}

		const auto snr = getSNR(distance, rair, rcrt);
		const auto spd = getSpeed(snr);
		map_.at(point.x).at(point.y) = spd;

		if (point.x == 0 && point.y == 0) {
			LOG(INFO) << "snr " << snr;
			LOG(INFO) << "spd " << spd;
		}

		return;
	}

	void Attenuation::normalize()
	{
		float max{ 0.0f };
		int inf_count{0};

		for (auto& row : map_)
			for (auto& value : row) {
				if (value > max)
					max = value;
				if (std::isinf(value))
					inf_count++;
			}

		LOG(INFO) << "inf count " << inf_count;
		LOG(INFO) << "normal max " << max;

		for (auto& row : map_)
			for (auto& value : row)
				value /= max;
	}

	float Attenuation::getNormalizedAttenuationValue(math::Vector2ui point)
	{
		return map_.at(point.x).at(point.y);
	}
}