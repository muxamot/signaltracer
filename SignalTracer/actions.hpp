#pragma once

#include "renderer.hpp"
#include "types.hpp"

namespace sgtr
{
	enum class UserAction {
		// coords
		UP,
		DOWN,
		LEFT,
		RIGHT,
		FORWARD,
		BACKWARD

		// angles
	};

	class ActionsController 
	{
	private:
		constexpr static float POSITION_SENSITIVITY = 0.1f;

		sptr<Renderer> renderer_;

	public:
		ActionsController(sptr<Renderer>);

		void onAction(const UserAction&);
	};
}