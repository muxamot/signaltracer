#pragma once

#include "renderer.hpp"
#include "cutting_plane.hpp"
#include "types.hpp"
#include "raycast.hpp"

namespace sgtr
{
	enum class Action {
		// coords
		UP,
		DOWN,
		LEFT,
		RIGHT,
		FORWARD,
		BACKWARD,

		//angle mode
		ROLL,

		//cplane
		CPLANE_CLIMB,
		CPLANE_DESCEND
	};

	struct UserAction 
	{
	public:
		Action action_;
		math::Vector2i delta_;
		int coeficient_{1};
	};

	class ActionsController 
	{
	private:
		constexpr static float POSITION_SENSITIVITY = 0.3f;
		constexpr static float ROTATION_SENSITIVITY = 0.5f;
		constexpr static float WHEEL_SENSITIVITY = 2.5f;
		constexpr static float CPLANE_SENSITIVITY = 2.5f; //0.05f;

		sptr<Renderer> renderer_;
		sptr<ÑuttingPlane> cplane_;
		sptr<Raycast> raycast_;
		void onMouseMove(const math::Vector2i&);

	public:
		ActionsController() = default;

		void onAction(const UserAction&);
		void set(sptr<Renderer>, sptr<ÑuttingPlane>, sptr<Raycast>);
	};
}