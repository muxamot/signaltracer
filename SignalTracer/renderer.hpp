#pragma once

#include "types.hpp"
#include "drawable_interface.hpp"
#include "shaders.hpp"
#include "pipeline.hpp"
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

		float cplane_offset_{0.0f};
		GLuint uworld_;

		math::Vector3f position_;
		math::Vector3f rotation_;

		void renderDrawable(sptr<IDrawable>);
		void renderCPlane(unsigned, unsigned);

	public:
		Renderer() = default;

		void init(sptr<Model>, sptr<IDrawable>, bool = true);
		void render(unsigned, unsigned);

		void applyPositionDelta(const math::Vector3f&);
		void applyRotationDelta(const math::Vector3f&);
	};
}