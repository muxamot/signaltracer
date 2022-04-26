#include <exception>

#include <gl/glew.h>
#include <glut.h>

#include "renderer.hpp"
#include "pipeline.hpp"
#include "vertex.hpp"
#include "logger.hpp"

namespace sgtr {

#define BUFFER_OFFSET(i) ((GLuint* )NULL + (i))

	GLuint World; //world
	unsigned num = 3;

	Renderer::Renderer() 
	{
		
	}

	void Renderer::init()
	{
		GLenum res = glewInit();
		if (res != GLEW_OK) {
			LOG(ERROR) << "GLEW initialization failed; glew says: " << glewGetErrorString(res);
			throw std::exception("Render initialization failed");
		}

		model_ = std::make_shared<Model>();
		model_->load();
		LOG(INFO) << "Render initialized";
	}

	void Renderer::render(unsigned viewport_w, unsigned viewport_h)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		math::Pipeline p;
		p.Rotate(90, 0, 0.0f);
		p.WorldPos(0.0f, 0.0f, 0.0f);
		p.SetPerspectiveProj(60.0f, viewport_w, viewport_h, 1.0f, 100.0f);

		glUniformMatrix4fv(World, 1, GL_TRUE, (const GLfloat*)p.GetWorldTrans().m);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, model_->VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(math::Vertex), 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(math::Vertex), (const GLvoid*)12);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model_->IBO);

		for (unsigned int i = 0; i < num; i++)
		{
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, BUFFER_OFFSET(i));
		}

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}

}
