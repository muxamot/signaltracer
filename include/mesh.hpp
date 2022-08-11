#pragma once

#include "drawable_interface.hpp"
#include "types.hpp"

namespace sgtr
{

class Mesh : public IDrawable
{
private:
    GLuint vbo_{INVALID_OGL_VALUE};
    GLuint ibo_{INVALID_OGL_VALUE};
    size_t index_count_{0};

public:
    explicit Mesh(const vertex_buf_t&, const index_buf_t&);
    ~Mesh() override;

    size_t getIndexCount() const override;
    GLuint getIndexBuffer() const override;
    GLuint getVertexBuffer() const override;
};

} // namespace sgtr