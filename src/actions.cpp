#include "actions.hpp"
#include "logger.hpp"
#include "vector.hpp"

namespace sgtr
{
void ActionsController::onMouseMove(const math::Vector2i& delta)
{
    renderer_->applyRotationDelta(math::Vector3f{-ROTATION_SENSITIVITY * static_cast<float>(delta.y),
                                                 ROTATION_SENSITIVITY * static_cast<float>(delta.x), 0.0f});
}

void ActionsController::onAction(const UserAction& act)
{
    switch (act.action_)
    {
    case Action::LEFT:
        renderer_->applyPositionDelta(math::Vector3f{POSITION_SENSITIVITY, 0.0f, 0.0f});
        break;
    case Action::RIGHT:
        renderer_->applyPositionDelta(math::Vector3f{-POSITION_SENSITIVITY, 0.0f, 0.0f});
        break;
    case Action::UP:
        renderer_->applyPositionDelta(math::Vector3f{0.0f, -POSITION_SENSITIVITY, 0.0f});
        break;
    case Action::DOWN:
        renderer_->applyPositionDelta(math::Vector3f{0.0f, POSITION_SENSITIVITY, 0.0f});
        break;
    case Action::FORWARD:
        renderer_->applyPositionDelta(
            math::Vector3f{0.0f, 0.0f, (act.coeficient_ * WHEEL_SENSITIVITY) * -POSITION_SENSITIVITY});
        break;
    case Action::BACKWARD:
        renderer_->applyPositionDelta(math::Vector3f{
            0.0f,
            0.0f,
            (act.coeficient_ * WHEEL_SENSITIVITY) * POSITION_SENSITIVITY,
        });
        break;
    case Action::ROLL:
        onMouseMove(act.delta_);
        break;
    case Action::CPLANE_CLIMB:
        cplane_->applyOffsetDelta(-CPLANE_SENSITIVITY);
        raycast_->updateMap(cplane_->offset());
        break;
    case Action::CPLANE_DESCEND:
        cplane_->applyOffsetDelta(CPLANE_SENSITIVITY);
        raycast_->updateMap(cplane_->offset());
        break;

    default:
        LOG(WARN) << "Undefined user action!";
        break;
    }
}

void ActionsController::set(sptr<Renderer> render, sptr<CuttingPlane> cplane, sptr<Raycast> rcast)
{
    renderer_ = std::move(render);
    cplane_ = std::move(cplane);
    raycast_ = std::move(rcast);
}

} // namespace sgtr