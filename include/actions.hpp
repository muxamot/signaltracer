#pragma once

#include "cutting_plane.hpp"
#include "raycast.hpp"
#include "renderer.hpp"
#include "types.hpp"

namespace sgtr
{

enum class Action
{
    // coords
    UP,
    DOWN,
    LEFT,
    RIGHT,
    FORWARD,
    BACKWARD,

    // angle mode
    ROLL,

    // cplane
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
    constexpr static float POSITION_SENSITIVITY = 1.0f;
    constexpr static float ROTATION_SENSITIVITY = 0.5f;
    constexpr static float WHEEL_SENSITIVITY = 5.5f;
    constexpr static float CPLANE_SENSITIVITY = 5.0f; // 0.05f;

    sptr<Renderer> renderer_;
    sptr<CuttingPlane> cplane_;
    sptr<Raycast> raycast_;
    void onMouseMove(const math::Vector2i&);

public:
    ActionsController() = default;

    void onAction(const UserAction&);
    void set(sptr<Renderer>, sptr<CuttingPlane>, sptr<Raycast>);
};

} // namespace sgtr