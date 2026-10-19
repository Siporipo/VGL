#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// Preprocessor macros
#define VGL_EXIT_FAILURE 0
#define VGL_EXIT_SUCCESS 1

#define VGL_COMPUTE_SHADER 		0xB0
#define VGL_VERTEX_SHADER 		0xB1
#define VGL_TESS_CONTROL_SHADER 	0xB2
#define VGL_TESS_EVALUATION_SHADER	0xB3
#define VGL_GEOMETRY_SHADER 		0xB4
#define VGL_FRAGMENT_SHADER 		0xB5


// Structs
typedef struct VGL_Monitor VGL_Monitor;
typedef struct VGL_Window  VGL_Window;

typedef struct VGL_VAO VGL_VAO;
typedef struct VGL_VBO VGL_VBO;
typedef struct VGL_ShaderProgram VGL_ShaderProgram;
typedef struct VGL_Shader        VGL_Shader;

// Master
int VGL_Init();
void VGL_Quit();

// GLFW
int VGL_GLFWInit();
void VGL_GLFWTerminate();

float VGL_GetTime();
void VGL_SetTime(float t);
void VGL_UpdateGLFW();
float VGL_GetFPS();

VGL_Monitor* VGL_GetMonitor();
int VGL_GetMonitorWidth(VGL_Monitor* monitor);
int VGL_GetMonitorHeight(VGL_Monitor* monitor);
int VGL_GetMonitorX(VGL_Monitor* monitor);
int VGL_GetMonitorY(VGL_Monitor* monitor);

bool VGL_WindowAlive(VGL_Window* window);
VGL_Window* VGL_CreateWindow(int width, int height, char *title, uint32_t flags, VGL_Monitor *monitor, VGL_Window* window_reference);
VGL_Window* VGL_DestroyWindow(VGL_Window* window);
void VGL_UpdateWindow(VGL_Window* window);

void VGL_PollEvents();
int VGL_WindowShouldClose(VGL_Window* window);

int VGL_GetWindowWidth(VGL_Window* window);
int VGL_GetWindowHeight(VGL_Window* window);
char* VGL_GetWindowTitle(VGL_Window* window);

// OpenGL
int VGL_GLInit(VGL_Window* window);
void VGL_GLAttachContext(VGL_Window* window);
void VGL_GLClearContext(float r, float g, float b, float a);

VGL_VAO* VGL_GLNewVAO();
VGL_VBO* VGL_GLNewVBO(VGL_VAO* VAO, float* vertices, int vertex_count, int* attribs, int attrib_count);
VGL_Shader* VGL_GLCompileShader(const char* code, uint32_t VGL_SHADER_TYPE);
VGL_ShaderProgram* VGL_GLLinkShader(VGL_Shader** shaders, int shader_count);
void VGL_GLDrawVAO(VGL_VAO* VAO, VGL_ShaderProgram* program);
