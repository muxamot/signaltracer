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
		bool left_handed_{true};

		sptr<Model> model_;
		sptr<Shaders> shaders_;
		sptr<IDrawable> cplane_;

		GLuint uworld_;

		math::Vector3f position_;
		math::Vector3f rotation_;

		void renderDrawable(sptr<IDrawable>);

	public:
		Renderer() = default;

		void init(sptr<Model>, sptr<IDrawable>, bool = true);
		void render(unsigned viewport_w, unsigned viewport_h);

		void applyPositionDelta(const math::Vector3f&);
		void applyRotationDelta(const math::Vector3f&);
	};
}