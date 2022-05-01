#pragma once

#include <vector>

#include "vector.hpp"
#include "opengl.hpp"

namespace sgtr {
	
	using ubyte_t = unsigned char;

	struct Pixel
	{
		ubyte_t r{ 0 };
		ubyte_t g{ 0 };
		ubyte_t b{ 0 };
	};
	
	class Heatmap
	{
	private:
		using heatmap_buf_t = std::vector<Pixel>;
		
		GLuint sampler_;
		unsigned width_;
		unsigned height_;
		heatmap_buf_t buffer_;
		math::Vector2f planeSpaceNearest(size_t, size_t);
		
		GLuint txo_;
		void generateTXObject();
		void updateTXObject();

	public:
		Heatmap(unsigned, unsigned);
	
		Pixel* at(size_t, size_t);
		void bind(GLenum);
		void setSampler(GLuint);
	};
}