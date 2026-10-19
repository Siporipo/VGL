#include "VGL_toolset.h"

int VGL_GLInit(VGL_Window* window) {
	glfwMakeContextCurrent(window->handle);
	static int window_count = 0;
	if (window_count++ == 0) {
		if (!gladLoadGL()) {
			fprintf(stderr, "VGL:GL - gladLoadGL() has failed from VGL_GLInit(), possibly upon VGL_CreateWindow()!\n");
			return VGL_EXIT_FAILURE;
		}
	
		printf("Renderer: %s.\n", glGetString(GL_RENDERER));
		printf("OpenGL version supported: %s.\n", glGetString(GL_VERSION));
	}
	
	// Simplifying the work in a simple program
	VGL_GLAttachContext(window);

	return VGL_EXIT_SUCCESS;
}

void VGL_GLAttachContext(VGL_Window* window) {
	if (!VGL_WindowAlive(window)) {
		return;
	}
	glfwMakeContextCurrent(window->handle);
	glfwGetFramebufferSize(window->handle, &window->width, &window->height);
	glViewport(0, 0, window->width, window->height);
}

void VGL_GLClearContext(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

VGL_VAO* VGL_GLNewVAO() {
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

VGL_VBO* VGL_GLNewVBO(VGL_VAO* VAO, float* vertices, int vertex_count, int* attribs, int attrib_count) {
	if (!VAO || !VAO->handle) {
		fprintf(stderr, "VGL:GL - Passed in an invalid VAO!\n");
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

	glBindVertexArray(VAO->handle);
	glBindBuffer(GL_ARRAY_BUFFER, VBO->handle);
	size_t len = 0;
	for (int i = 0; i < attrib_count; i++) {
		len += sizeof(float) * attribs[i];
	}
	glBufferData(GL_ARRAY_BUFFER, vertex_count * len, vertices, GL_STATIC_DRAW);

	size_t b_offset = 0;
	for (int i = 0; i < attrib_count; i++) {
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, attribs[i], GL_FLOAT, GL_FALSE, len, (void*)b_offset);
		b_offset += attribs[i] * sizeof(float);
	}

	VAO->vertex_count += vertex_count;

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return VBO;
}

VGL_Shader* VGL_GLCompileShader(const char* code, uint32_t VGL_SHADER_TYPE) {
	if (!code) {
		fprintf(stderr, "VGL:GL - Passed in code of value NULL for shader compilation!\n");
		return NULL;
	}

	VGL_Shader* shader = gc_malloc(sizeof(VGL_Shader));
	switch (VGL_SHADER_TYPE) {
		case VGL_VERTEX_SHADER:
			VGL_SHADER_TYPE = GL_VERTEX_SHADER;
			break;
		case VGL_FRAGMENT_SHADER:
			VGL_SHADER_TYPE = GL_FRAGMENT_SHADER;
			break;
		//case VGL_COMPUTE_SHADER:
			//VGL_SHADER_TYPE = GL_COMPUTE_SHADER;
			//break;
		//case VGL_TESS_CONTROL_SHADER:
			//VGL_SHADER_TYPE = GL_TESS_CONTROL_SHADER;
			//break;
		//case VGL_TESS_EVALUATION_SHADER:
			//VGL_SHADER_TYPE = GL_TESS_EVALUATION_SHADER;
			//break;
		case VGL_GEOMETRY_SHADER:
			VGL_SHADER_TYPE = GL_GEOMETRY_SHADER;
			break;
		default:
			fprintf(stderr, "VGL:GL - Invalid shader type for creation!\n");
			gc_free(shader);
			return NULL;
	}
	shader->handle = glCreateShader(VGL_SHADER_TYPE);
	if (!shader->handle) {
		fprintf(stderr, "VGL:GL - Failed to create shader!\n");
		gc_free(shader);
		return NULL;
	}

	glShaderSource(shader->handle, 1, &code, NULL);
	glCompileShader(shader->handle);

	return shader;
}

VGL_ShaderProgram* VGL_GLLinkShader(VGL_Shader** shaders, int shader_count) {
	if (!shaders || shader_count < 1) {
		fprintf(stderr, "VGL:GL - Failed to link no shaders, stupid user!\n");
	}

	VGL_ShaderProgram* program = gc_malloc(sizeof(VGL_ShaderProgram));
	program->handle = glCreateProgram();
	if (!program->handle) {
		fprintf(stderr, "VGL:GL - Shader program generation failed!\n");
		gc_free(program);
		return NULL;
	}

	for (int i = 0; i < shader_count; i++) {
		if (!shaders[i] || !shaders[i]->handle) {
			fprintf(stderr, "VGL:GL - NULL shader passed, continuing!\n");
			continue;
		}
		glAttachShader(program->handle, shaders[i]->handle);
	}

	glLinkProgram(program->handle);

	return program;
}

void VGL_GLDrawVAO(VGL_VAO* VAO, VGL_ShaderProgram* program) {
	glUseProgram(program->handle);
	glBindVertexArray(VAO->handle);

	glDrawArrays(GL_TRIANGLES, 0, VAO->vertex_count);

	glUseProgram(0);
	glBindVertexArray(0);
}
