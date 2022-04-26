#include <exception>

#include <gl/glew.h>
#include <glut.h>

#include "renderer.hpp"
#include "pipeline.hpp"
#include "vertex.hpp"
#include "logger.hpp"

#define BUFFER_OFFSET(i) ((GLuint* )NULL + (sizeof(unsigned) * 3 * i))

namespace sgtr {

	unsigned num = 3;
	float a = 0;
	float b = 0;
	float c = 0;

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

		shaders_ = std::make_shared<Shaders>();
		uworld_ = shaders_->setUniform("gWorld");

		LOG(INFO) << "Render initialized";
	}

	void Renderer::render(unsigned viewport_w, unsigned viewport_h)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		math::Pipeline p;

		//a += 0.01;
		b += 0.3;
		//c += 0.01;

		p.Rotate(a, b, c);
		p.WorldPos(0.0f, 0.0f, 30.0f);
		p.SetPerspectiveProj(75.0f, viewport_w, viewport_h, 1.0f, 10000.0f);

		glUniformMatrix4fv(uworld_, 1, GL_TRUE, (const GLfloat*)p.GetWorldTrans().m);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, model_->VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(math::Vertex), 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(math::Vertex), (const GLvoid*)12);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model_->IBO);

		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0); //draw in 1 pass TODO draw in multiple pass
		
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}

}
