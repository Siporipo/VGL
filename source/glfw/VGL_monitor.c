#include "VGL_toolset.h"

/*
 * Getting the main monitor.
 */
VGL_Monitor* VGL_GetMonitor() {
	VGL_Monitor* monitor = gc_malloc(sizeof(VGL_Monitor));

	monitor->handle = glfwGetPrimaryMonitor();
	if (!monitor->handle) {
		fprintf(stderr, "VGL:GLFW - Failed to get monitor!\n");
		return NULL;
	}

	glfwGetMonitorWorkarea(
		monitor->handle,
		&monitor->x,
		&monitor->y,
		&monitor->width,
		&monitor->height
	);
	if (monitor->width == 0) {
		fprintf(stderr, "VGL:GLFW - Failed to get monitor workarea!\n");
		return NULL;
	}

	return monitor;
}

/*
 * Monitor handle value dereferencing.
 */
int VGL_GetMonitorWidth(VGL_Monitor* monitor) {
	if (!monitor) {
		fprintf(stderr, "VGL:GLFW - Passed in NULL monitor pointer for dereferencing!\n");
		return VGL_EXIT_FAILURE;
	}
	return monitor->width;
}
int VGL_GetMonitorHeight(VGL_Monitor* monitor) {
	if (!monitor) {
		fprintf(stderr, "VGL:GLFW - Passed in NULL monitor pointer for dereferencing!\n");
		return VGL_EXIT_FAILURE;
	}
	return monitor->height;
}
int VGL_GetMonitorX(VGL_Monitor* monitor) {
	if (!monitor) {
		fprintf(stderr, "VGL:GLFW - Passed in NULL monitor pointer for dereferencing!\n");
		return VGL_EXIT_FAILURE;
	}
	return monitor->x;
}
int VGL_GetMonitorY(VGL_Monitor* monitor) {
	if (!monitor) {
		fprintf(stderr, "VGL:GLFW - Passed in NULL monitor pointer for dereferencing!\n");
		return VGL_EXIT_FAILURE;
	}
	return monitor->y;
}

