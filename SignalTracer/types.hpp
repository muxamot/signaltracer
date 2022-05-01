#pragma once

#include <memory>
#include <vector>

#include "vertex.hpp"
#include "drawable_interface.hpp"

namespace sgtr {

	template<typename T>
	using sptr = std::shared_ptr<T>;

	template<typename T>
	using uptr = std::unique_ptr<T>;

	template<typename T>
	using wptr = std::weak_ptr<T>;

	using vertex_buf_t = std::vector<math::Vertex>;
	using index_buf_t = std::vector<unsigned int>;
	using drawable_list_t = std::vector<sptr<IDrawable>>;
}