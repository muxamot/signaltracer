#include <exception>

#include "opengl.hpp"
#include "renderer.hpp"
#include "vertex.hpp"
#include "logger.hpp"

#define BUFFER_OFFSET(i) ((GLuint* )NULL + (sizeof(unsigned) * 3 * i))

namespace sgtr {

	void Renderer::applyPositionDelta(const math::Vector3f& delta)
	{
		position_ += delta;
	}

	void Renderer::applyRotationDelta(const math::Vector3f& delta)
	{
		rotation_ += delta;
	}

	void Renderer::init(sptr<Model> model, sptr<IDrawable> cplane, bool left_handed)
	{
		GLenum res = glewInit();
		if (res != GLEW_OK) {
			LOG(ERROR) << "GLEW initialization failed; glew says: " << glewGetErrorString(res);
			throw std::exception("Render initialization failed");
		}

		model_ = std::move(model);
		cplane_ = std::move(cplane);
		shaders_ = std::make_shared<Shaders>();
		uworld_ = shaders_->setUniform("gWorld");
		left_handed_ = left_handed;

		LOG(INFO) << "Render initialized";
	}

	void Renderer::render(unsigned viewport_w, unsigned viewport_h)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		
		if (!model_) {
			LOG(ERROR) << "Called render with invalid model";
			throw std::exception("Invalid model");
		}
			
		math::Pipeline p;
		p.Rotate((left_handed_) ? 90 + rotation_.x : rotation_.x, rotation_.y, rotation_.z);
		p.WorldPos(position_.x, position_.y, position_.z);
		p.SetPerspectiveProj(75.0f, viewport_w, viewport_h, 0.1f, 10000.0f);

		glUniformMatrix4fv(uworld_, 1, GL_TRUE, (const GLfloat*)p.GetWorldTrans().m);

		for (const auto& drawable : *model_)
			renderDrawable(drawable);

		renderCPlane(viewport_w, viewport_h);
	}

	void Renderer::renderDrawable(sptr<IDrawable> drawable)
	{
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, drawable->getVertexBuffer());
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(math::Vertex), 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(math::Vertex), (const GLvoid*)12);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, drawable->getIndexBuffer());

		glDrawElements(GL_TRIANGLES, drawable->getIndexCount(), GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}

	void Renderer::renderCPlane(unsigned vw, unsigned vh)
	{
		math::Pipeline p;
		p.Rotate((left_handed_) ? 90 + rotation_.x : rotation_.x, rotation_.y, rotation_.z);
		p.WorldPos(position_.x, position_.y, position_.z + cplane_offset_);
		p.SetPerspectiveProj(75.0f, vw, vh, 0.1f, 10000.0f);
		glUniformMatrix4fv(uworld_, 1, GL_TRUE, (const GLfloat*)p.GetWorldTrans().m);

		renderDrawable(cplane_);
	}

}
