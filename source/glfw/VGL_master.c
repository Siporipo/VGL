#include "VGL_toolset.h"

inline int VGL_GLFWInit() {
	if (!glfwInit()) {
		fprintf(stderr, "VGL:GlFW - Failed to initialize GLFW!\n");
		return VGL_EXIT_FAILURE;
	}
	return VGL_EXIT_SUCCESS;
}

inline void VGL_GLFWTerminate() {
	glfwTerminate();
}
