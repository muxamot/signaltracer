#pragma once

#include <array>

#include "drawable_interface.hpp"
#include "vertex.hpp"

namespace sgtr
{
	class ÑuttingPlane : public IDrawable
	{
		constexpr static size_t VERTEX_COUNT{ 4 };
		constexpr static size_t INDEX_COUNT{ 6 };

		constexpr static std::array<unsigned int, INDEX_COUNT> index_ = { 3, 0, 1, 1, 2, 3 };
		std::array<math::Vertex, VERTEX_COUNT> vertex_;

		float offset_{ 0.1 };
		float wx_, wy_;
		GLuint vb_;
		GLuint ib_;
		
		void updateVertices();
		void createVB();
		void updateVB();
		void createIB();

	public:
		ÑuttingPlane(float, float);
		~ÑuttingPlane() override = default;
		
		void createPlane();
		void applyOffsetDelta(float);
		float offset() const;

		size_t getIndexCount() const override;
		GLuint getIndexBuffer() const override;
		GLuint getVertexBuffer() const override;
	};

}