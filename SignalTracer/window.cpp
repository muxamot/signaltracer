#include "window.hpp"
#include "logger.hpp"

namespace sgtr {

	Window::Window(WindowDescriptor desc)
		: desc_(desc)
	{
		sdl_init();
	}

	Window::~Window()
	{
		SDL_DestroyWindow(sdl_window_);
	}

	void Window::sdl_init()
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			LOG(ERROR) << "Unable to init SDL, error: " << SDL_GetError();
			exit(1);
		}

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);

		sdl_window_ = SDL_CreateWindow("Signal Tracer 3D View",
										SDL_WINDOWPOS_CENTERED,
										SDL_WINDOWPOS_CENTERED,
										desc_.width_, 
										desc_.height_,
										SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

		sdl_glcontext_ = SDL_GL_CreateContext(sdl_window_); 

		if (!sdl_window_) {
			LOG(ERROR) << "Failed to create SDL window, SDL says: " << SDL_GetError();
			exit(1);
		}

		LOG(INFO) << "Initialized SDL window";

		// OpenGL init

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 
		glClearDepth(1.0);
		glDepthFunc(GL_LESS);
		glEnable(GL_DEPTH_TEST); 
		glShadeModel(GL_SMOOTH);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, (float)desc_.width_ / (float)desc_.height_, 0.1f, 100.0f);
		glMatrixMode(GL_MODELVIEW); 
	}

	bool Window::event_polling()
	{
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			switch (event.type) { 
			case SDL_QUIT:
				return false;

			//keypress processing
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) { 
				case SDLK_ESCAPE:
					return false;
				}
				break;
			}
		}

		return true;
	}

	void Window::redraw()
	{
		desc_.redraw_callback_();
	}

	int Window::display()
	{
		while (event_polling()) {
			redraw();

			glFlush();
			SDL_GL_SwapWindow(sdl_window_);
		}

		SDL_Quit(); // завершаем работу SDL и выходим

		return 0;
	}
}