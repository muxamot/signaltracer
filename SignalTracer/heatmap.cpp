#include "heatmap.hpp"

namespace sgtr
{
	Heatmap::Heatmap(unsigned width, unsigned height)
		: width_(width), height_(height)
	{
		buffer_.resize(width_ * height_);
		
		for (auto& pix : buffer_)
			pix = { 50, 50, 50 };

		generateTXObject();
	}

	void Heatmap::generateTXObject()
	{
		glGenTextures(1, &txo_);
		glBindTexture(GL_TEXTURE_2D, txo_);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer_.data());
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	void Heatmap::updateTXObject()
	{
		glBindTexture(GL_TEXTURE_2D, txo_);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width_, height_, GL_RGB, GL_UNSIGNED_BYTE, buffer_.data());
	}

	void Heatmap::setSampler(GLuint sampler)
	{
		sampler_ = sampler;
		glUniform1i(sampler_, 0);
	}

	void Heatmap::applyChanges()
	{
		updateTXObject();
	}

	Pixel& Heatmap::at(size_t x, size_t y)
	{
		return buffer_.at(x * width_ + y);
	}

	void Heatmap::bind(GLenum unit)
	{
		glActiveTexture(unit);
		glBindTexture(GL_TEXTURE_2D, txo_);
	}
}