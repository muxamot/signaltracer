#include "actions.hpp"
#include "logger.hpp"
#include "vector.hpp"

namespace sgtr
{
	ActionsController::ActionsController(sptr<Renderer> render)
		: renderer_(std::move(render)) {}

	void ActionsController::onAction(const UserAction& act)
	{
		switch (act)
		{
		case UserAction::LEFT: renderer_->applyPositionDelta(math::Vector3f{ POSITION_SENSITIVITY, 0.0f, 0.0f }); break;
		case UserAction::RIGHT: renderer_->applyPositionDelta(math::Vector3f{ -POSITION_SENSITIVITY, 0.0f, 0.0f }); break;
		case UserAction::UP: renderer_->applyPositionDelta(math::Vector3f{ 0.0f, -POSITION_SENSITIVITY, 0.0f }); break;
		case UserAction::DOWN: renderer_->applyPositionDelta(math::Vector3f{ 0.0f, POSITION_SENSITIVITY, 0.0f }); break;
		case UserAction::FORWARD: renderer_->applyPositionDelta(math::Vector3f{ 0.0f, 0.0, -POSITION_SENSITIVITY }); break;
		case UserAction::BACKWARD: renderer_->applyPositionDelta(math::Vector3f{ 0.0f, 0.0f, POSITION_SENSITIVITY, }); break;

			default:
				LOG(WARN) << "Undefined user action!";
				break;
		}
	}

}