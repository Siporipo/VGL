#include "VGL_toolset.h"

VGL_Shader* VGL_GLCompileShader(const char* code, VGL_ShaderType shader_type) {
	if (!VGL_GLInit(NULL)) {
		fprintf(stderr, "VGL:GL - OpenGL not active with at least one window!\n");
		return NULL;
	}

	if (!code) {
		fprintf(stderr, "VGL:GL - Passed in code of value NULL for shader compilation!\n");
		return NULL;
	}

	VGL_Shader* shader = gc_malloc(sizeof(VGL_Shader));
	switch (shader_type) {
		case VGL_VERTEX_SHADER:
			shader_type = GL_VERTEX_SHADER;
			break;
		case VGL_FRAGMENT_SHADER:
			shader_type = GL_FRAGMENT_SHADER;
			break;
		//case VGL_COMPUTE_SHADER:
			//shader_type = GL_COMPUTE_SHADER;
			//break;
		//case VGL_TESS_CONTROL_SHADER:
			//shader_type = GL_TESS_CONTROL_SHADER;
			//break;
		//case VGL_TESS_EVALUATION_SHADER:
			//shader_type = GL_TESS_EVALUATION_SHADER;
			//break;
		case VGL_GEOMETRY_SHADER:
			shader_type = GL_GEOMETRY_SHADER;
			break;
		default:
			fprintf(stderr, "VGL:GL - Invalid shader type for creation!\n");
			gc_free(shader);
			return NULL;
	}
	shader->handle = glCreateShader(shader_type);
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
	if (!VGL_GLInit(NULL)) {
		fprintf(stderr, "VGL:GL - OpenGL not active with at least one window!\n");
		return NULL;
	}

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

VGL_Shader* VGL_GLLoadShader(const char* path, VGL_ShaderType shader_type) {
	if (!VGL_GLInit(NULL)) {
		fprintf(stderr, "VGL:GL - OpenGL not active with at least one window!\n");
		return NULL;
	}

	FILE* fptr = fopen(path, "r");
	if (!fptr) {
		fprintf(stderr, "VGL:GL - Shader code file could not open!\n");
		return NULL;
	}

	rewind(fptr);
	char c = fgetc(fptr);
	size_t file_len = 0;
	while (c != EOF) {
		c = fgetc(fptr);
		file_len++;
	}

	rewind(fptr);
	char shader_code[file_len + 1];
	for (size_t i = 0; i < file_len; i++) {
		shader_code[i] = fgetc(fptr);
	}

	return VGL_GLCompileShader(shader_code, shader_type);
}




