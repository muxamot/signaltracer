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

	GLuint Renderer::getUniformAddr(const std::string & name) const
	{
		return shaders_->setUniform(name);
	}

	void Renderer::init(sptr<Model> model, sptr<IDrawable> cplane, sptr<Heatmap> hmap, sptr<IDrawable> marker, bool left_handed)
	{
		GLenum res = glewInit();
		if (res != GLEW_OK) {
			LOG(ERROR) << "GLEW initialization failed; glew says: " << glewGetErrorString(res);
			throw std::exception("Render initialization failed");
		}

		shaders_ = std::make_shared<Shaders>();
		model_ = std::move(model);
		cplane_ = std::move(cplane);
		hmap_ = std::move(hmap);
		marker_ = std::move(marker);

		uworld_ = getUniformAddr("gWorld");
		hmap_->setSampler(getUniformAddr("Sampler0"));
		usampler_ = getUniformAddr("SamplingEnabled");
		umono_ = getUniformAddr("MonocolorEnabled");
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
		glUniform1i(usampler_, 0);

		for (const auto& drawable : model_->getDrawableItems())
			renderDrawable(drawable);

		glUniform1i(umono_, 1);
		renderDrawable(marker_);
		glUniform1i(umono_, 0);

		renderCPlane(viewport_w, viewport_h);
	}

	void Renderer::renderDrawable(sptr<IDrawable> drawable)
	{
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		// passing vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, drawable->getVertexBuffer());

		// layout in vertex attrib array - 3 floats (12 bytes) vertex coords, 2 float texture coords 
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE_SIZE, (const GLvoid*)VERTEX_COORDS_OFFSET);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, STRIDE_SIZE, (const GLvoid*)TEXTURE_COORDS_OFFSET);
		
		// passing index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, drawable->getIndexBuffer());

		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(drawable->getIndexCount()), GL_UNSIGNED_INT, 0);

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
		glUniform1i(usampler_, 1);

		hmap_->bind(GL_TEXTURE0);

		renderDrawable(cplane_);
	}

}
