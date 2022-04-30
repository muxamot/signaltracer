#pragma once

#include "drawable_interface.hpp"

namespace sgtr
{
	class �uttingPlane : public IDrawable
	{
		float offset_{ 0.0 };
		constexpr static size_t index_count_{6};
		GLuint vb_;
		GLuint ib_;
		
		void createVB(float, float);
		void createIB();

	public:
		�uttingPlane(float, float);
		~�uttingPlane() override = default;
		
		void offsetTransform(float);

		size_t getIndexCount() const override;
		GLuint getIndexBuffer() const override;
		GLuint getVertexBuffer() const override;
	};

}