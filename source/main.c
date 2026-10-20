#include "VGL.h"

int main() {
	if (!VGL_Init()) return -1;

	VGL_Window* window1 = VGL_CreateWindow(300, 200, "1", 0, NULL, NULL);

	VGL_Shader* shaders[] = {
		VGL_GLLoadShader("/home/valts/Desktop/VGL/bin/shaders/shader.vert", VGL_VERTEX_SHADER),
		VGL_GLLoadShader("/home/valts/Desktop/VGL/bin/shaders/shader.frag", VGL_FRAGMENT_SHADER)
	};
	VGL_ShaderProgram* shader = VGL_GLLinkShader(shaders, 2);

	float vertices[] = {
		-1, -1,  1, 0, 0,
		 1, -1,  0, 1, 0,
		 1,  1,  0, 0, 1,
		-1,  1,  0, 1, 0
	};
	int attribs[2] = {2, 3};
	VGL_VBO* VBO = VGL_GLNewVBO(vertices, 6, 5);

	VGL_Index indices[] = {
		0, 1, 2,
		2, 3, 0
	};
	VGL_EBO* EBO = VGL_GLNewEBO(indices, 6);

	VGL_VAO* VAO1 = VGL_GLNewVAO();
	VGL_GLAddVBO(VAO1, VBO, attribs, 2);
	VGL_GLAddEBO(VAO1, EBO);

	while (!VGL_WindowShouldClose(window1)) {
		VGL_GLAttachContext(window1);
		VGL_GLClearContext(1, 1, 0, 1);
		VGL_GLDrawVAO(VAO1, shader, EBO);
		VGL_UpdateWindow(window1);

		VGL_UpdateGLFW();
	}

	VGL_Quit();
	return 0;
}
