#pragma once

#include "types.hpp"
#include "drawable_interface.hpp"
#include "shaders.hpp"
#include "vector.hpp"

namespace sgtr
{
	class Renderer
	{
	private:
		sptr<Model> model_;
		sptr<Shaders> shaders_;

		GLuint uworld_;

		math::Vector3f position_;
		math::Vector3f rotation_;

	public:
		Renderer() = default;

		void init(sptr<Model>);
		void render(unsigned viewport_w, unsigned viewport_h);

		void applyPositionDelta(const math::Vector3f&);
		void applyRotationDelta(const math::Vector3f&);
	};
}