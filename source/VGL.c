#include "VGL_toolset.h"

int VGL_Init() {
	if (VGL_GLFWInit() == VGL_EXIT_FAILURE) {
		fprintf(stderr, "VGL - VGL_GLFWInit() has failed from VGL_Init()!\n");
		return VGL_EXIT_FAILURE;
	}
	return VGL_EXIT_SUCCESS;
}

void VGL_Quit() {
	VGL_GLFWTerminate();
	gc_free_all();
}
