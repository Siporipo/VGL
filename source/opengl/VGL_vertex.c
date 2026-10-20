#include "VGL_toolset.h"


VGL_VAO* VGL_GLNewVAO() {
	if (!VGL_GLInit(NULL)) {
		fprintf(stderr, "VGL:GL - OpenGL not active with at least one window!\n");
		return NULL;
	}

	VGL_VAO* VAO = gc_malloc(sizeof(VAO));
	VAO->vertex_count = 0;
	glGenVertexArrays(1, &VAO->handle);
	if (!VAO->handle) {
		fprintf(stderr, "VGL:GL - Failed to generate a VAO!\n");
		gc_free(VAO);
		return NULL;
	}

	return VAO;
}

VGL_VBO* VGL_GLNewVBO(float* vertices, int vertex_count, int vertex_stride) {
	if (!VGL_GLInit(NULL)) {
		fprintf(stderr, "VGL:GL - OpenGL not active with at least one window!\n");
		return NULL;
	}

	VGL_VBO* VBO = gc_malloc(sizeof(VGL_VBO));
	VBO->vertex_count = vertex_count;
	glGenBuffers(1, &VBO->handle);
	if (!VBO->handle) {
		fprintf(stderr, "VGL:GL - Something went wrong generating a VBO!\n");
		gc_free(VBO);
		return NULL;
	}

	glBindBuffer(GL_ARRAY_BUFFER, VBO->handle);
	glBufferData(GL_ARRAY_BUFFER, vertex_count * vertex_stride * sizeof(float), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return VBO;
}

int VGL_GLAddVBO(VGL_VAO* VAO, VGL_VBO* VBO, int* attribs, int attrib_count) {
	if (!VGL_GLInit(NULL)) {
		fprintf(stderr, "VGL:GL - OpenGL not active with at least one window!\n");
		return VGL_EXIT_FAILURE;
	}

	if (!VAO || !VAO->handle) {
		fprintf(stderr, "VGL:GL - Passed in an invalid VAO!\n");
		return VGL_EXIT_FAILURE;
	}
	if (!VBO || !VBO->handle) {
		fprintf(stderr, "VGL:GL - Passed in an invalid VBO!\n");
		return VGL_EXIT_FAILURE;
	}

	glBindVertexArray(VAO->handle);
	glBindBuffer(GL_ARRAY_BUFFER, VBO->handle);

	size_t len = 0;
	for (int i = 0; i < attrib_count; i++) {
		len += attribs[i];
	}

	size_t b_offset = 0;
	for (int i = 0; i < attrib_count; i++) {
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, attribs[i], GL_FLOAT, GL_FALSE, len * sizeof(float), (void*)b_offset);
		//printf("glVertexAttribPointer(%d, %d, GL_FLOAT, GL_FALSE, %zu, %p);\n", i, attribs[i], len * sizeof(float), (void*)b_offset);
		b_offset += attribs[i] * sizeof(float);
	}

	VAO->vertex_count += VBO->vertex_count;

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return VGL_EXIT_SUCCESS;
}

VGL_EBO* VGL_GLNewEBO(VGL_Index* indices, int index_count) {
	if (!VGL_GLInit(NULL)) {
		fprintf(stderr, "VGL:GL - OpenGL not active with at least one window!\n");
		return NULL;
	}

	VGL_EBO* EBO = gc_malloc(sizeof(VGL_EBO));
	EBO->index_count = index_count;
	glGenBuffers(1, &EBO->handle);
	if (!EBO->handle) {
		fprintf(stderr, "VGL:GL - Something went wrong generating an EBO!\n");
		gc_free(EBO);
		return NULL;
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO->handle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(VGL_Index) * index_count, indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return EBO;
}

int VGL_GLAddEBO(VGL_VAO* VAO, VGL_EBO* EBO) {
	if (!VGL_GLInit(NULL)) {
		fprintf(stderr, "VGL:GL - OpenGL not active with at least one window!\n");
		return VGL_EXIT_FAILURE;
	}

	if (!VAO || !VAO->handle) {
		fprintf(stderr, "VGL:GL - Passed in an invalid VAO!\n");
		return VGL_EXIT_FAILURE;
	}
	if (!EBO || !EBO->handle) {
		fprintf(stderr, "VGL:GL - Passed in an invalid EBO!\n");
		return VGL_EXIT_FAILURE;
	}

	glBindVertexArray(VAO->handle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO->handle);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return VGL_EXIT_SUCCESS;
}
