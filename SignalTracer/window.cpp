#include "opengl.hpp"
#include "window.hpp"
#include "logger.hpp"

namespace sgtr {

	Window::Window(WindowDescriptor desc)
		: desc_(desc)
	{
		sdlInit();
	}

	Window::~Window()
	{
		SDL_DestroyWindow(sdl_window_);
		SDL_FreeCursor(sdl_cursor_);
	}

	void Window::sdlInit()
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			LOG(ERROR) << "Unable to init SDL, error: " << SDL_GetError();
			exit(1);
		}

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);

		sdl_window_ = SDL_CreateWindow("Signal Tracer 3D View",
										SDL_WINDOWPOS_CENTERED,
										SDL_WINDOWPOS_CENTERED,
										desc_.width_, 
										desc_.height_,
										SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

		sdl_glcontext_ = SDL_GL_CreateContext(sdl_window_); 

		if (!sdl_window_) {
			LOG(ERROR) << "Failed to create SDL window, SDL says: " << SDL_GetError();
			exit(1);
		}

		SDL_GL_SetSwapInterval(1);

		sdl_cursor_ = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL);
		SDL_SetCursor(sdl_cursor_);

		LOG(INFO) << "Initialized SDL window";

		GLenum res = glewInit();
		if (res != GLEW_OK) {
			LOG(ERROR) << "GLEW initialization failed; glew says: " << glewGetErrorString(res);
			throw std::exception("Render initialization failed");
		}

		LOG(INFO) << "Initialized GLEW";

		// OpenGL init

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 
		glEnable(GL_DEPTH_TEST);
	}

	void Window::keyboardEvent(SDL_Keycode kcode)
	{
		Action act;
		switch (kcode)
		{
			//keys mapping
			case SDLK_UP: act = Action::UP; break;
			case SDLK_DOWN: act = Action::DOWN; break;
			case SDLK_LEFT: act = Action::LEFT; break;
			case SDLK_RIGHT: act = Action::RIGHT; break;
			case SDLK_w: act = Action::FORWARD; break;
			case SDLK_s: act = Action::BACKWARD; break;
			case SDLK_q: act = Action::CPLANE_CLIMB; break;
			case SDLK_a: act = Action::CPLANE_DESCEND; break;

			default:
				LOG(WARN) << "No handler for this button, try another!";
				return;
		}

		desc_.action_callback_(UserAction{ act });
	}

	void Window::onMouseButton(MouseState state)
	{
		if (state == DOWN) {
			if (SDL_CaptureMouse(SDL_TRUE) != 0)
				LOG(WARN) << "Mouse capturing is not supported - you have really strange system.";

			SDL_GetRelativeMouseState(&x_, &y_);

			drag_ = true;
			return;
		}

		SDL_CaptureMouse(SDL_FALSE);
		drag_ = false;
	}

	void Window::onWheelStroke(int scroll)
	{
		Action act = (scroll > 0) ? Action::FORWARD : Action::BACKWARD;
		desc_.action_callback_(UserAction{ act, {},  std::abs(scroll) });
	}

	bool Window::eventPolling()
	{
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			switch (event.type) { 
			case SDL_QUIT:
				return false;
			//mouse events
			case SDL_MOUSEWHEEL:
				onWheelStroke(event.wheel.y);
				break;
			case SDL_MOUSEBUTTONDOWN:
				onMouseButton(DOWN);
				break;
			case SDL_MOUSEBUTTONUP:
				onMouseButton(UP);
				break;
			//keypress processing
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) { 
				case SDLK_ESCAPE:
					return false;
				default:
					keyboardEvent(event.key.keysym.sym);
				}
				break;
			}
		}

		if (drag_) {
			SDL_GetRelativeMouseState(&x_, &y_);
			desc_.action_callback_(UserAction{ Action::ROLL, math::Vector2i{x_, y_} });
		}

		return true;
	}

	void Window::redraw()
	{
		desc_.redraw_callback_();
	}

	int Window::display()
	{
		while (eventPolling()) {
			redraw();

			glFlush();
			SDL_GL_SwapWindow(sdl_window_);
		}

		SDL_Quit(); // завершаем работу SDL и выходим

		return 0;
	}
}