#pragma once

#include "types.hpp"
#include "model.hpp"
#include "shaders.hpp"

namespace sgtr
{
	class Renderer
	{
	private:
		sptr<Model> model_;
		sptr<Shaders> shaders_;

		GLuint uworld_;

	public:
		Renderer();

		void render(unsigned viewport_w, unsigned viewport_h);
		void init();
	};
}