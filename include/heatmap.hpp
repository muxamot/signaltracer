#pragma once

#include <vector>

#include "opengl.hpp"
#include "types.hpp"
#include "vector.hpp"

namespace sgtr
{

using ubyte_t = unsigned char;

struct Pixel
{
    ubyte_t r{0};
    ubyte_t g{0};
    ubyte_t b{0};
};

class Heatmap
{
private:
    using heatmap_buf_t = std::vector<Pixel>;

    GLuint sampler_;
    unsigned width_;
    unsigned height_;
    heatmap_buf_t buffer_;

    GLuint txo_;
    void generateTXObject();
    void updateTXObject();
    Pixel& at(size_t, size_t);

public:
    Heatmap(heatmap_res_t);

    void setLevelAt(float, size_t, size_t);
    void bind(GLenum);
    void setSampler(GLuint);
    void applyChanges();
    math::Vector2ui getResolution();
};
} // namespace sgtr