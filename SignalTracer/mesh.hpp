#pragma once

#include <vector>

#include "drawable_interface.hpp"
#include "vertex.hpp"

namespace sgtr
{
	class Mesh : public IDrawable
	{
	private:
		GLuint vbo_{INVALID_OGL_VALUE};
		GLuint ibo_{INVALID_OGL_VALUE};
		size_t index_count_{0};
		
	public:
		explicit Mesh(const std::vector<math::Vertex>&, const std::vector<unsigned int>&);
		~Mesh() override;
		
		size_t getIndexCount() const override;
		GLuint getIndexBuffer() const override;
		GLuint getVertexBuffer() const override;
	};
}