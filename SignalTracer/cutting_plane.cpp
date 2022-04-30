#include "cutting_plane.hpp"

#include "vertex.hpp"

namespace sgtr {
	
	ÑuttingPlane::ÑuttingPlane(float wx, float wy)
	{
		createVB(wx / 2.0f, wy / 2.0f);
		createIB();
	}

	void ÑuttingPlane::offsetTransform(float delta)
	{
		offset_ += delta;
	}

	void ÑuttingPlane::createVB(float x, float y)
	{
		using namespace math;

		Vertex vertex[] = {
			Vertex{Vector3f{ x, y, offset_ }, {}},
			Vertex{Vector3f{ x, -y, offset_ }, {}},
			Vertex{Vector3f{ -x, -y, offset_ }, {}},
			Vertex{Vector3f{ -x, y, offset_ }, {}}
		};

		glGenBuffers(1, &vb_);
		glBindBuffer(GL_ARRAY_BUFFER, vb_);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
	}

	void ÑuttingPlane::createIB()
	{
		unsigned int index[index_count_] = { 3, 0, 1, 1, 2, 3 };

		glGenBuffers(1, &ib_);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
	}

	size_t ÑuttingPlane::getIndexCount() const
	{
		return index_count_;
	}

	GLuint ÑuttingPlane::getIndexBuffer() const
	{
		return ib_;
	}

	GLuint ÑuttingPlane::getVertexBuffer() const
	{
		return vb_;
	}

}
