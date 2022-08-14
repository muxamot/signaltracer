#include "heatmap.hpp"

namespace sgtr
{

Heatmap::Heatmap(heatmap_res_t res)
    : width_(res.x_)
    , height_(res.y_)
{
    buffer_.resize(width_ * height_);

    for (auto& pix : buffer_)
        pix = {50, 50, 50};

    generateTXObject();
}

void Heatmap::generateTXObject()
{
    glGenTextures(1, &txo_);
    glBindTexture(GL_TEXTURE_2D, txo_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer_.data());
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Heatmap::updateTXObject()
{
    glBindTexture(GL_TEXTURE_2D, txo_);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width_, height_, GL_RGB, GL_UNSIGNED_BYTE, buffer_.data());
}

void Heatmap::setSampler(GLuint sampler)
{
    sampler_ = sampler;
    glUniform1i(sampler_, 0);
}

void Heatmap::applyChanges()
{
    updateTXObject();
}

math::Vector2ui Heatmap::getResolution()
{
    return math::Vector2ui{width_, height_};
}

Pixel& Heatmap::at(size_t x, size_t y)
{
    return buffer_.at(x * width_ + y);
}

void Heatmap::setLevelAt(float normalized_level, size_t x, size_t y)
{
    // blue zone
    if (normalized_level <= 0.005)
    {
        at(x, y) = {3, 1, 140};
        return;
    }
    if (normalized_level <= 0.15)
    {
        at(x, y) = {66, 89, 195};
        return;
    }
    if (normalized_level <= 0.3)
    {
        at(x, y) = {158, 194, 255};
        return;
    }

    // green zone
    if (normalized_level <= 0.4)
    {
        at(x, y) = {0, 128, 2};
        return;
    }
    if (normalized_level <= 0.5)
    {
        at(x, y) = {118, 219, 115};
        return;
    }
    if (normalized_level <= 0.6)
    {
        at(x, y) = {198, 255, 202};
        return;
    }

    // yellow zone
    if (normalized_level <= 0.7)
    {
        at(x, y) = {255, 201, 3};
        return;
    }
    if (normalized_level <= 0.8)
    {
        at(x, y) = {255, 233, 97};
        return;
    }
    if (normalized_level <= 0.9)
    {
        at(x, y) = {255, 255, 159};
        return;
    }

    // red zone
    at(x, y) = {255, 0, 0};
}

void Heatmap::bind(GLenum unit)
{
    glActiveTexture(unit);
    glBindTexture(GL_TEXTURE_2D, txo_);
}

} // namespace sgtr