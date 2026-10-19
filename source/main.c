#include "VGL.h"
#include <stdio.h>
#include <math.h>

int main() {
	if (!VGL_Init()) return -1;

	VGL_Window *window1 = VGL_CreateWindow(80, 59, "My window", 0, NULL, NULL);

	while (!VGL_WindowShouldClose(window1)) {
		VGL_UpdateWindow(window1);
		VGL_UpdateGLFW();
	}

	VGL_Quit();
	return 0;
}
