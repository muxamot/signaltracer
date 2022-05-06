#pragma once

#include "drawable_interface.hpp"
#include "vector.hpp"

namespace sgtr
{
	class Marker : public IDrawable
	{
	private:
		constexpr static size_t VERTEX_COUNT_{ 5 };
		constexpr static size_t INDEX_COUNT_{ 18 };
		
		GLuint ib_{ INVALID_OGL_VALUE };
		GLuint vb_{ INVALID_OGL_VALUE };

		void createVB(math::Vector3f pos);
		void createIB();

	public:
		Marker(math::Vector3f);

		size_t getIndexCount() const;
		GLuint getIndexBuffer() const;
		GLuint getVertexBuffer() const;
	};
}