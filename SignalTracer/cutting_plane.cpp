#include "cutting_plane.hpp"

#include "vertex.hpp"

namespace sgtr {

	�uttingPlane::�uttingPlane(float wx, float wy)
		: wx_(wx / 2.0f), wy_(wy / 2.0f) {}

	void �uttingPlane::createPlane()
	{
		updateVertices();
		createVB();
		createIB();
	}

	void �uttingPlane::applyOffsetDelta(float delta)
	{
		offset_ += delta;
		updateVertices();
		updateVB();
	}

	float �uttingPlane::offset() const
	{
		return offset_;
	}

	void �uttingPlane::updateVertices()
	{
		using namespace math;
		vertex_ = {
			Vertex{ Vector3f{ wx_, wy_, offset_ }, Vector2f{ 1.0f, 0.0f } },
			Vertex{ Vector3f{ wx_, -wy_, offset_ }, Vector2f{ 1.0f, 1.0f } },
			Vertex{ Vector3f{ -wx_, -wy_, offset_ }, Vector2f{ 0.0f, 1.0f } },
			Vertex{ Vector3f{ -wx_, wy_,  offset_ }, Vector2f{ 0.0f, 0.0f } }
		};
	}

	void �uttingPlane::createVB()
	{	
		glGenBuffers(1, &vb_);
		glBindBuffer(GL_ARRAY_BUFFER, vb_);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_), vertex_.data(), GL_DYNAMIC_DRAW);
	}

	void �uttingPlane::updateVB()
	{
		glNamedBufferSubData(vb_, 0, sizeof(vertex_), vertex_.data());
	}

	void �uttingPlane::createIB()
	{
		glGenBuffers(1, &ib_);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_), index_.data(), GL_DYNAMIC_DRAW);
	}

	size_t �uttingPlane::getIndexCount() const
	{
		return INDEX_COUNT;
	}

	GLuint �uttingPlane::getIndexBuffer() const
	{
		return ib_;
	}

	GLuint �uttingPlane::getVertexBuffer() const
	{
		return vb_;
	}

}
