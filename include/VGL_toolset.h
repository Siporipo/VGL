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


typedef struct VGL_VBO {
	GLuint handle;
	int vertex_count;
} VGL_VBO;

typedef struct VGL_VAO {
	GLuint handle;
	int vertex_count;
} VGL_VAO;

typedef struct VGL_Shader {
	GLuint handle;
} VGL_Shader;

typedef struct VGL_ShaderProgram {
	GLuint handle;
} VGL_ShaderProgram;
