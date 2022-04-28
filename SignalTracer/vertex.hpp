#pragma once

#include "vector.hpp"

namespace math
{
	struct Vertex
	{
		Vector3f m_pos;
		Vector2f m_tex;

		Vertex() = default;
		Vertex(Vector3f pos, Vector2f tex)
			: m_pos(pos), m_tex(tex) {}
	};

}