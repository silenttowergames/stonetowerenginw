#include <stdio.h>
#include "ShaderFunctions.h"
#include "../Application/ApplicationState.h"

Shader Shader_Create(ApplicationState* app, char* key)
{
	Shader shader;
	memset(&shader, 0, sizeof(Shader));
	
	const char* formatStr = "assets/shaders/%s.fxb";
	
	shader.key = key;
	shader.filename = malloc(sizeof(char) * (strlen(formatStr) + strlen(key) + 1 - 2)); // Shader.filename allocate
	
	sprintf(shader.filename, formatStr, shader.key);
	
	FILE *effectFile = fopen(shader.filename, "rb");
	fseek(effectFile, 0, SEEK_END);
	uint32_t effectCodeLength = ftell(effectFile);
	fseek(effectFile, 0, SEEK_SET);
	uint8_t *effectCode = malloc(effectCodeLength);
	fread(effectCode, 1, effectCodeLength, effectFile);
	fclose(effectFile);
	FNA3D_CreateEffect(app->renderState.device, effectCode, effectCodeLength, &shader.effect, &shader.effectData);
	free(effectCode);
	
	return shader;
}

void Shader_Free(Shader* shader)
{
	free(shader->filename);
}
