#include "VGL_toolset.h"

float dt = 0.0f;


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


float VGL_GetTime() {
	return (float)glfwGetTime();
}
void VGL_SetTime(float t) {
	glfwSetTime(t);
}
float VGL_GetFPS() {
	return 1.0f / dt;
}

static void vgl_tickfps() {
	static float new_t = 0;
	static float old_t = 0;
	old_t = new_t;
	new_t = VGL_GetTime();
	
	dt = new_t - old_t;
}
void VGL_UpdateGLFW() {
	VGL_PollEvents();
	vgl_tickfps();
}
