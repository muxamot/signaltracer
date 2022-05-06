#include <array>

#include "marker.hpp"
#include "vertex.hpp"

namespace sgtr
{	
	void Marker::createVB(math::Vector3f pos)
	{
		using namespace math;
		const std::array<math::Vertex, VERTEX_COUNT_> vertex = {
			Vertex{ pos + Vector3f{ 0.0f, 0.0f, 0.1f}, Vector2f{} }, 
			Vertex{ pos + Vector3f{ -0.1f, -0.1f, -0.1f}, Vector2f{} }, 
			Vertex{ pos + Vector3f{ 0.1f, -0.1f, -0.1f }, Vector2f{} }, 
			Vertex{ pos + Vector3f{ 0.1f, 0.1f,  -0.1f }, Vector2f{} }, 
			Vertex{ pos + Vector3f{ -0.1f, 0.1f,  -0.1f }, Vector2f{} }
		};

		glGenBuffers(1, &vb_);
		glBindBuffer(GL_ARRAY_BUFFER, vb_);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex.data(), GL_STATIC_DRAW);
	}

	void Marker::createIB()
	{
		const std::array<unsigned int, INDEX_COUNT_> index = {
			0, 1, 2,
			0, 1, 4,
			0, 4, 3,
			0, 3, 2,
			1, 4, 2,
			4, 2, 3
		};

		glGenBuffers(1, &ib_);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index.data(), GL_STATIC_DRAW);
	}

	Marker::Marker(math::Vector3f position)
	{
		createVB(std::move(position));
		createIB();
	}

	size_t Marker::getIndexCount() const
	{
		return INDEX_COUNT_;
	}

	GLuint Marker::getIndexBuffer() const
	{
		return ib_;
	}

	GLuint Marker::getVertexBuffer() const
	{
		return vb_;
	}

}
