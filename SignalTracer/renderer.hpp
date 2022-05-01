#pragma once

#include "types.hpp"
#include "drawable_interface.hpp"
#include "shaders.hpp"
#include "pipeline.hpp"
#include "vertex.hpp"
#include "heatmap.hpp"

namespace sgtr
{
	class Renderer
	{
	private:
		constexpr static auto STRIDE_SIZE = sizeof(math::Vertex);

		//layout
		constexpr static auto VERTEX_COORDS_OFFSET = 0U;
		constexpr static auto TEXTURE_COORDS_OFFSET = (sizeof(float) * 3);

		bool left_handed_{true};

		sptr<Model> model_;
		sptr<Shaders> shaders_;
		sptr<IDrawable> cplane_;
		sptr<Heatmap> hmap_;

		float cplane_offset_{0.0f};
		GLuint uworld_;
		GLuint usampler_;

		math::Vector3f position_;
		math::Vector3f rotation_;

		GLuint getUniformAddr(const std::string&) const;

		void renderDrawable(sptr<IDrawable>);
		void renderCPlane(unsigned, unsigned);

	public:
		Renderer() = default;

		void init(sptr<Model>, sptr<IDrawable>, sptr<Heatmap>, bool = true);
		void render(unsigned, unsigned);
		
		void applyPositionDelta(const math::Vector3f&);
		void applyRotationDelta(const math::Vector3f&);
	};
}