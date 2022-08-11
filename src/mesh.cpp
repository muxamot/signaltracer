#include <exception>

#include "logger.hpp"
#include "mesh.hpp"
#include "opengl.hpp"

namespace sgtr
{

Mesh::Mesh(const vertex_buf_t& vertices, const index_buf_t& indexes)
{
    index_count_ = indexes.size();
    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(math::Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glGenBuffers(1, &ibo_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * index_count_, indexes.data(), GL_STATIC_DRAW);

    if (vbo_ == INVALID_OGL_VALUE || ibo_ == INVALID_OGL_VALUE)
    {
        LOG(ERROR) << "Failed to build OpenGL buffers for given model mesh";
        throw std::runtime_error("Failed to build OpenGL buffers");
    }

    LOG(INFO) << "Generated vertex and index OpenGL buffers";
}

Mesh::~Mesh()
{
    if (vbo_ != INVALID_OGL_VALUE)
        glDeleteBuffers(1, &vbo_);

    if (ibo_ != INVALID_OGL_VALUE)
        glDeleteBuffers(1, &ibo_);
}

size_t Mesh::getIndexCount() const
{
    return index_count_;
}
GLuint Mesh::getIndexBuffer() const
{
    return ibo_;
}
GLuint Mesh::getVertexBuffer() const
{
    return vbo_;
}
} // namespace sgtr