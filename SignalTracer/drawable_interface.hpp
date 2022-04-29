#pragma once

#include <vector>

#include "opengl.hpp"
#include "types.hpp"

namespace sgtr 
{
	class IDrawable 
	{
	public:
		virtual ~IDrawable() = default;
		
		virtual size_t getIndexCount() const = 0;
		virtual GLuint getIndexBuffer() const = 0;
		virtual GLuint getVertexBuffer() const = 0;
	};

	using Model = std::vector<sptr<IDrawable>>;
}