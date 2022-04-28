#pragma once

#include <glut.h>

#include "vertex.hpp"

namespace sgtr
{
	class Model
	{
	public:
		GLuint VBO;
		GLuint IBO;

		Model() = default;

		void load();
	private:

		void createVertexBuffer();
		void createIndexBuffer();
	};


}