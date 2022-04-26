#include <exception>

#include <gl/glew.h>

#include "model.hpp"
#include "logger.hpp"

namespace sgtr {

	void Model::load()
	{
		try {
			CreateVertexBuffer();
			CreateIndexBuffer();
		}
		catch (const std::exception& ex)
		{
			LOG(ERROR) << "Got exception while building - " << ex.what();
		}
	}

	void Model::CreateVertexBuffer()
	{
		using namespace math;

		Vertex Vertices[7] = {
			Vertex(Vector3f(10.0f, 10.0f, 1.0f), Vector2f(1,1)),
			Vertex(Vector3f(10.0f, -10.0f, 1.0f), Vector2f(0, 1)),
			Vertex(Vector3f(-10.0f, -10.0f, 1.0f), Vector2f(0,0)),
			Vertex(Vector3f(-10.0f, 10.0f, 1.0f), Vector2f(1,0)),

			Vertex(Vector3f(-2.0f, 5.0f, 1.0f), Vector2f(1,0)),
			Vertex(Vector3f(-8.0f, 5.0f, 1.0f), Vector2f(0,0)),
			Vertex(Vector3f(-5.0f, 5.0f, -5.0f), Vector2f(0.5,1)) };

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	}

	void Model::CreateIndexBuffer()
	{
		unsigned int Indices[] =
		{ 0, 1, 2,
		  2, 3, 0,
		  4, 5, 6 };

		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
	}

}