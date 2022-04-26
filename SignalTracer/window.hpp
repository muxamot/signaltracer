#pragma once

#include <functional>

#include <SDL.h>
#include <glut.h>

#include "types.hpp"
#include "actions.hpp"

namespace sgtr {
	using redraw_cb_t = std::function<void()>;
	using kpress_cb_t = std::function<void(UserAction)>;

	struct WindowDescriptor
	{
		redraw_cb_t redraw_callback_;
		kpress_cb_t keypress_callback_;
		
		int width_;
		int height_;
	};

	class Window
	{
	public:
		Window() = delete;
		Window(Window&&) = delete;

		explicit Window(WindowDescriptor);
		~Window();

		int display();

	private:
		WindowDescriptor desc_;
		
		SDL_Window* sdl_window_;
		SDL_GLContext sdl_glcontext_; 

		void sdl_init();
		bool event_polling();
		void redraw();
	};
}