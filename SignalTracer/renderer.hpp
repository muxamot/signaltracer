#pragma once

#include "types.hpp"
#include "model.hpp"

namespace sgtr
{
	class Renderer
	{
	private:
		sptr<Model> model_;

	public:
		Renderer();

		void render(unsigned viewport_w, unsigned viewport_h);
		void init();
	};
}