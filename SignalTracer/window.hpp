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
		kpress_cb_t action_callback_;
		
		int width_;
		int height_;
	};

	enum MouseState
	{
		UP,
		DOWN
	};

	class Window
	{
	private:
		WindowDescriptor desc_;
		bool drag_{ false };
		int x_{ 0 };
		int y_{ 0 };

		SDL_Window* sdl_window_;
		SDL_GLContext sdl_glcontext_;
		SDL_Cursor* sdl_cursor_;

		void sdlInit();
		bool eventPolling();
		void redraw();
		void keyboardEvent(SDL_Keycode);

		void onMouseButton(MouseState);
		void onWheelStroke(int);

	public:
		Window() = delete;
		Window(Window&&) = delete;

		explicit Window(WindowDescriptor);
		~Window();

		int display();
	};
}