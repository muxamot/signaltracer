#pragma once

#include "renderer.hpp"
#include "types.hpp"

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
		ROLL
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

		sptr<Renderer> renderer_;
		void onMouseMove(const math::Vector2i&);

	public:
		ActionsController(sptr<Renderer>);

		void onAction(const UserAction&);
	};
}