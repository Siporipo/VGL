#include "VGL_toolset.h"

/*
 * Helper to know if a window is alive.
 */
bool VGL_WindowAlive(VGL_Window* window) {
	if (window) return (bool)(window->handle);
	return false;
}

//static void VGL_ParseWindowHints(uint32_t flags) {
	//if (flags & VGL_WINDOW_RESIZABLE) {
		//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	//}
//}

/*
 * Creating a window handle.
 */
VGL_Window* VGL_CreateWindow(
		int width, int height,
		char *title,
		uint32_t flags,
		VGL_Monitor *monitor,
		VGL_Window* window_reference
) {
//	VGL_ParseWindowHints(flags);

	GLFWwindow* ptr;
	if (!window_reference || !window_reference->handle) {
		ptr = glfwCreateWindow(width, height, title, NULL, NULL);
	} else {
		ptr = glfwCreateWindow(width, height, title, NULL, window_reference->handle);
	}
	
	if (!ptr) {
		fprintf(stderr, "VGL:GLFW - Failed to create window!\n");
		return NULL;
	}
	VGL_Window* window = gc_malloc(sizeof(VGL_Window));
	*window = (VGL_Window){
		.width=width,
		.height=height,
		.title=title,
		.flags=flags,
		.handle=ptr
	};
	
	VGL_GLInit(window);
	glfwSwapInterval(1);

	return window;
}

/*
 * Destroying a window handle.
 */
VGL_Window* VGL_DestroyWindow(VGL_Window* window) {
	if (window == NULL) {
		return NULL;
	}
	glfwDestroyWindow(window->handle);
	window->handle = NULL;
	gc_free(window);
	return NULL;
}

/*
 * Run a window tick.
 */
void VGL_UpdateWindow(VGL_Window *window) {
	if (!VGL_WindowAlive(window)) {
		fprintf(stderr, "VGL:GLFW - Tried to update a closed window!\n");
		return;
	}
	glfwSwapBuffers(window->handle);
	return;
}

void VGL_PollEvents() {
	glfwPollEvents();
}

/*
 * Should a window be open?
 */
int VGL_WindowShouldClose(VGL_Window* window) {
	if (!VGL_WindowAlive(window) || glfwWindowShouldClose(window->handle)) {
		return VGL_EXIT_SUCCESS;
	}
	return VGL_EXIT_FAILURE;
}

/*
 * Dereferencing window struct values.
 */
int VGL_GetWindowWidth(VGL_Window* window) {
	if (!VGL_WindowAlive(window)) {
		fprintf(stderr, "VGL:GLFW - Passed a NULL window pointer for dereferencing!\n");
		return VGL_EXIT_FAILURE;
	}
	return window->width;
}
int VGL_GetWindowHeight(VGL_Window* window) {
	if (!VGL_WindowAlive(window)) {
		fprintf(stderr, "VGL:GLFW - Passed a NULL window pointer for dereferencing!\n");
		return VGL_EXIT_FAILURE;
	}
	return window->height;
}
char* VGL_GetWindowTitle(VGL_Window* window) {
	if (!VGL_WindowAlive(window)) {
		fprintf(stderr, "VGL:GLFW - Passed a NULL window pointer for dereferencing!\n");
		return VGL_EXIT_FAILURE;
	}
	return window->title;
}
