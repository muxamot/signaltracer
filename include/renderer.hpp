#pragma once

#include "drawable_interface.hpp"
#include "heatmap.hpp"
#include "marker.hpp"
#include "model.hpp"
#include "pipeline.hpp"
#include "shaders.hpp"
#include "types.hpp"
#include "vertex.hpp"

namespace sgtr
{

class Renderer
{
private:
    constexpr static auto STRIDE_SIZE = sizeof(math::Vertex);

    // layout
    constexpr static auto VERTEX_COORDS_OFFSET = 0U;
    constexpr static auto TEXTURE_COORDS_OFFSET = (sizeof(float) * 3);

    bool left_handed_{true};

    sptr<Model> model_;
    sptr<Shaders> shaders_;
    sptr<IDrawable> cplane_;
    sptr<Heatmap> hmap_;
    sptr<IDrawable> marker_;

    float cplane_offset_{0.0f};
    GLuint uworld_;
    GLuint usampler_;
    GLuint umono_;

    math::Vector3f position_;
    math::Vector3f rotation_;

    GLuint getUniformAddr(const std::string&) const;

    void renderDrawable(sptr<IDrawable>);
    void renderCPlane(unsigned, unsigned);

public:
    Renderer() = default;

    void init(sptr<Model>, sptr<IDrawable>, sptr<Heatmap>, sptr<IDrawable>, bool = true);
    void render(unsigned, unsigned);

    void applyPositionDelta(const math::Vector3f&);
    void applyRotationDelta(const math::Vector3f&);
};

} // namespace sgtr