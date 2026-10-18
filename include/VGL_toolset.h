#pragma once

// Standard libs
#include <stdlib.h>
#include <stdio.h>

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include <math.h>
#include <errno.h>

// Dependencies
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "garbage_collector/garbage_collector.h"

#include "VGL.h"

// Preprocessor macros
#define VGL_EXIT_FAILURE 0
#define VGL_EXIT_SUCCESS 1

// Structs
typedef struct VGL_Window {
	int width, height;
	char *title;
	GLFWwindow* handle;
	uint32_t flags;
} VGL_Window;

typedef struct VGL_Monitor {
	GLFWmonitor* handle;
	int width, height;
	int x, y;
} VGL_Monitor;
