#include "VGL_toolset.h"

int VGL_GLInit(VGL_Window* window) {
	glfwMakeContextCurrent(window->handle);
	static int window_count = 0;
	if (window_count++ == 0) {
		if (!gladLoadGL()) {
			fprintf(stderr, "VGL:GL - gladLoadGL() has failed from VGL_GLInit(), possibly upon VGL_CreateWindow()!\n");
			VGL_Quit();
			return VGL_EXIT_FAILURE;
		}
	
		printf("Renderer: %s.\n", glGetString(GL_RENDERER));
		printf("OpenGL version supported: %s.\n", glGetString(GL_VERSION));
	}
	
	// Simplifying the work in a simple program
	VGL_GLAttachContext(window);

	return VGL_EXIT_SUCCESS;
}

void VGL_GLAttachContext(VGL_Window* window) {
	if (!VGL_WindowAlive(window)) {
		glfwMakeContextCurrent(NULL);
		return;
	}
	glfwMakeContextCurrent(window->handle);
	glfwGetFramebufferSize(window->handle, &window->width, &window->height);
	glViewport(0, 0, window->width, window->height);
}

void VGL_GLClearContext(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}
