#include "cutting_plane.hpp"

#include "vertex.hpp"

namespace sgtr
{

CuttingPlane::CuttingPlane(float wx, float wy)
    : wx_(wx / 2.0f)
    , wy_(wy / 2.0f)
{
}

void CuttingPlane::createPlane()
{
    updateVertices();
    createVB();
    createIB();
}

void CuttingPlane::applyOffsetDelta(float delta)
{
    offset_ += delta;
    updateVertices();
    updateVB();
}

float CuttingPlane::offset() const
{
    return offset_;
}

void CuttingPlane::updateVertices()
{
    using namespace math;
    vertex_ = {Vertex{Vector3f{wx_, wy_, offset_}, Vector2f{1.0f, 0.0f}},
               Vertex{Vector3f{wx_, -wy_, offset_}, Vector2f{1.0f, 1.0f}},
               Vertex{Vector3f{-wx_, -wy_, offset_}, Vector2f{0.0f, 1.0f}},
               Vertex{Vector3f{-wx_, wy_, offset_}, Vector2f{0.0f, 0.0f}}};
}

void CuttingPlane::createVB()
{
    glGenBuffers(1, &vb_);
    glBindBuffer(GL_ARRAY_BUFFER, vb_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_), vertex_.data(), GL_DYNAMIC_DRAW);
}

void CuttingPlane::updateVB()
{
    glNamedBufferSubData(vb_, 0, sizeof(vertex_), vertex_.data());
}

void CuttingPlane::createIB()
{
    glGenBuffers(1, &ib_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_), index_.data(), GL_DYNAMIC_DRAW);
}

size_t CuttingPlane::getIndexCount() const
{
    return INDEX_COUNT;
}

GLuint CuttingPlane::getIndexBuffer() const
{
    return ib_;
}

GLuint CuttingPlane::getVertexBuffer() const
{
    return vb_;
}

} // namespace sgtr
