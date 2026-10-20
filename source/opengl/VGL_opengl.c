#include "VGL_toolset.h"

int VGL_WINDOW_COUNT = 0;

int VGL_GLInit(VGL_Window* window) {
	if (window == NULL) {
		if (VGL_WINDOW_COUNT < 1) {
			return VGL_EXIT_FAILURE;
		}
		return VGL_EXIT_SUCCESS;
	}

	glfwMakeContextCurrent(window->handle);
	if (VGL_WINDOW_COUNT++ == 0) {
		if (!gladLoadGL()) {
			fprintf(stderr, "VGL:GL - gladLoadGL() has failed from VGL_GLInit(), possibly upon VGL_CreateWindow()!\n");
			return VGL_EXIT_FAILURE;
		}
	
		printf("Renderer: %s.\n", glGetString(GL_RENDERER));
		printf("OpenGL version supported: %s.\n", glGetString(GL_VERSION));
	}
	
	// Simplifying the work in a simple program
	VGL_GLAttachContext(window);

	return VGL_EXIT_SUCCESS;
}

