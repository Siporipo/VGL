#include "VGL.h"
#include <stdio.h>
#include <math.h>

int main() {
	if (!VGL_Init()) return -1;

	VGL_Window* window1 = VGL_CreateWindow(300, 200, "1", 0, NULL, NULL);
	VGL_Window* window2 = VGL_CreateWindow(400, 900, "2", 0, NULL, window1);

	const char vertex_code[] = 
		"#version 460\n"
		"layout(location = 0) in vec2 v_pos;\n"
		"layout(location = 1) in vec3 color;\n"
		"out vec4 v_color;\n"
		"void main() {\n"
		"	gl_Position = vec4(v_pos, 0, 1);\n"
		"	v_color = vec4(color, 1);\n"
		"}";
	const char fragment_code1[] = 
		"#version 460\n"
		"in vec4 v_color;\n"
		"out vec4 f_color;\n"
		"void main() {\n"
		"	f_color = v_color;\n"
		"}";
	const char fragment_code2[] = 
		"#version 460\n"
		"in vec4 v_color;\n"
		"out vec4 f_color;\n"
		"void main() {\n"
		"	f_color = vec4(0, 0, 1, 1);\n"
		"}";

	VGL_Shader* vs = VGL_GLCompileShader(vertex_code, VGL_VERTEX_SHADER);
	VGL_Shader* fs1 = VGL_GLCompileShader(fragment_code1, VGL_FRAGMENT_SHADER);
	VGL_Shader* fs2 = VGL_GLCompileShader(fragment_code2, VGL_FRAGMENT_SHADER);
	VGL_Shader* shaders1[2] = {vs, fs1};
	VGL_Shader* shaders2[2] = {vs, fs2};
	VGL_ShaderProgram* shader1 = VGL_GLLinkShader(shaders1, 2);
	VGL_ShaderProgram* shader2 = VGL_GLLinkShader(shaders2, 2);

	float vertices[15] = {
		-1, -1, 1, 1, 1,
		 1, -1, 1, 1, 1,
		 0,  1, 1, 1, 1
	};
	int attribs[2] = {2, 3};

	VGL_GLAttachContext(window1);
	VGL_VAO* VAO1 = VGL_GLNewVAO();
	VGL_VBO* VBO1 = VGL_GLNewVBO(VAO1, vertices, 3, attribs, 2);

	VGL_GLAttachContext(window2);
	VGL_VAO* VAO2 = VGL_GLNewVAO();
	VGL_VBO* VBO2 = VGL_GLNewVBO(VAO2, vertices, 3, attribs, 2);


	while (!VGL_WindowShouldClose(window1)) {
		if (VGL_WindowShouldClose(window2)) break;

		VGL_GLAttachContext(window2);
		VGL_GLClearContext(0, 1, 0.5f, 1);
		VGL_GLDrawVAO(VAO2, shader2);
		VGL_UpdateWindow(window2);

		VGL_GLAttachContext(window1);
		VGL_GLClearContext(1, 1, 0, 1);
		VGL_GLDrawVAO(VAO1, shader1);
		VGL_UpdateWindow(window1);

		VGL_UpdateGLFW();
	}

	VGL_Quit();
	return 0;
}
