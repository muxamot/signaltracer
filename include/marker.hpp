#pragma once

#include "access_point.hpp"
#include "drawable_interface.hpp"
#include "types.hpp"
#include "vector.hpp"

namespace sgtr
{

class Marker : public IDrawable
{
private:
    constexpr static size_t VERTEX_BY_MARKER_COUNT_{5};
    constexpr static size_t INDEX_BY_MARKER_COUNT_{18};

    size_t idx_count_;
    GLuint ib_{INVALID_OGL_VALUE};
    GLuint vb_{INVALID_OGL_VALUE};

    void createVB(const ap_vec_t& ap_list);
    size_t createIB(size_t);

public:
    Marker(sptr<ap_vec_t>);

    size_t getIndexCount() const;
    GLuint getIndexBuffer() const;
    GLuint getVertexBuffer() const;
};

} // namespace sgtr