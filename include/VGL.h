#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// Structs
typedef struct VGL_Monitor VGL_Monitor;
typedef struct VGL_Window  VGL_Window;

// Master
int VGL_Init();
void VGL_Quit();

// GLFW
int VGL_GLFWInit();
void VGL_GLFWTerminate();

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

