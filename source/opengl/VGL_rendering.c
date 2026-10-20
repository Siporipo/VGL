#include "VGL_toolset.h"

void VGL_GLAttachContext(VGL_Window* window) {
	if (!VGL_GLInit(NULL)) {
		fprintf(stderr, "VGL:GL - OpenGL not active with at least one window!\n");
		return;
	}

	if (!VGL_WindowAlive(window)) {
		fprintf(stderr, "VGL:GL - Tried attaching to destroyed window context!\n");
		return;
	}
	glfwMakeContextCurrent(window->handle);
	glfwGetFramebufferSize(window->handle, &window->width, &window->height);
	glViewport(0, 0, window->width, window->height);
}

void VGL_GLClearContext(float r, float g, float b, float a) {
	if (!VGL_GLInit(NULL)) {
		fprintf(stderr, "VGL:GL - OpenGL not active with at least one window!\n");
		return;
	}

	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void VGL_GLDrawVAO(VGL_VAO* VAO, VGL_ShaderProgram* program, VGL_EBO* EBO) {
	if (!VGL_GLInit(NULL)) {
		fprintf(stderr, "VGL:GL - OpenGL not active with at least one window!\n");
		return;
	}

	glUseProgram(program->handle);
	glBindVertexArray(VAO->handle);

	if (!EBO || !EBO->handle) {
		glDrawArrays(GL_TRIANGLES, 0, VAO->vertex_count);
	} else {
		glDrawElements(GL_TRIANGLES, EBO->index_count, GL_UNSIGNED_INT, 0);
	}

	glUseProgram(0);
	glBindVertexArray(0);
}
