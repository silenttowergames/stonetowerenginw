#include <flecs.h>
#include <FNA3D.h>
#include "FinalizeScreenSystem.h"
#include "../../Application/ApplicationStateFunctions.h"
#include "../../Rendering/CameraFunctions.h"
#include "../../Rendering/SpriteBatchFunctions.h"
#include "../../Utilities/float4d.h"
#include "../../Utilities/quadFunctions.h"

static void FinalizeScreenSystem_ToRTs(ApplicationState* app)
{
	if(!app->renderState.spriteBatch.opened)
	{
		SpriteBatch_Begin(&app->renderState.spriteBatch);
		
		return;
	}
	
	FNA3D_SetViewport(app->renderState.device, &app->renderState.viewport);
	
	FNA3D_SetRenderTargets(
		app->renderState.device,
		&app->renderState.mainRenderTarget.binding,
		1,
		NULL,
		FNA3D_DEPTHFORMAT_NONE
	);
	
	FNA3D_BeginFrame(app->renderState.device);
	
	FNA3D_Vec4 color = { 1, 0.5f, 1, 1, };
	FNA3D_Clear(
		app->renderState.device,
		FNA3D_CLEAROPTIONS_TARGET,
		&color,
		0,
		0
	);
	
	MOJOSHADER_effectParam* shaderMatrix = Shader_ParamGet(&app->renderState.shaderSpriteEffect, "MatrixTransform");
	assert(shaderMatrix != NULL);
	Camera_LoadInto(&app->renderState.mainRenderTarget.camera, shaderMatrix->value.values);
	
	MOJOSHADER_effectStateChanges stateChanges;
	memset(&stateChanges, 0, sizeof(stateChanges));
	FNA3D_ApplyEffect(app->renderState.device, app->renderState.shaderSpriteEffect.effect, 0, &stateChanges);
	if(app->assetManager.arrayShader[0].update != NULL)
	{
		app->assetManager.arrayShader[0].update(&app->assetManager.arrayShader[0]);
	}
	if(!app->assetManager.arrayShader[0].disabled)
	{
		FNA3D_ApplyEffect(app->renderState.device, app->assetManager.arrayShader[0].effect, 0, &stateChanges);
	}
	
	SpriteBatch_Flush(&app->renderState);
	
	SpriteBatch_End(&app->renderState.spriteBatch);
}

static void FinalizeScreenSystem_ToWindow(ApplicationState* app)
{
	FNA3D_Viewport viewport;
	viewport.w = app->renderState.resolution.X;
	viewport.h = app->renderState.resolution.Y;
	viewport.x = 0;
	viewport.y = 0;
	FNA3D_SetViewport(
		app->renderState.device,
		&viewport
	);
	
	FNA3D_SetRenderTargets(
		app->renderState.device,
		NULL,
		0,
		NULL,
		FNA3D_DEPTHFORMAT_NONE
	);
	
	FNA3D_BeginFrame(app->renderState.device);
	
	FNA3D_Vec4 color = { 0, 0, 0, 1, };
	FNA3D_Clear(
		app->renderState.device,
		FNA3D_CLEAROPTIONS_TARGET,
		&color,
		0,
		0
	);
	
	SpriteBatch_Begin(&app->renderState.spriteBatch);
	
	quad pos = quad_Easy(
		app->renderState.mainRenderTarget.position.X,
		app->renderState.mainRenderTarget.position.Y,
		app->renderState.mainRenderTarget.size.X,
		app->renderState.mainRenderTarget.size.Y,
		0,
		0,
		0
	);
	quad src = (quad){
		{ 0, 0, },
		{ 1, 0, },
		{ 0, 1, },
		{ 1, 1, },
	};
	SpriteBatch_AddQuad(
		&app->renderState.spriteBatch,
		&app->renderState.camera,
		app->renderState.mainRenderTarget.texture.asset,
		pos,
		src,
		colorU(255, 255, 255, 255)
	);
	
	MOJOSHADER_effectParam* shaderMatrix = Shader_ParamGet(&app->renderState.shaderSpriteEffect, "MatrixTransform");
	assert(shaderMatrix != NULL);
	Camera_LoadInto(&app->renderState.camera, shaderMatrix->value.values);
	
	MOJOSHADER_effectStateChanges stateChanges;
	memset(&stateChanges, 0, sizeof(stateChanges));
	FNA3D_ApplyEffect(app->renderState.device, app->renderState.shaderSpriteEffect.effect, 0, &stateChanges);
	if(app->assetManager.arrayShader[0].update != NULL)
	{
		app->assetManager.arrayShader[0].update(&app->assetManager.arrayShader[0]);
	}
	if(!app->assetManager.arrayShader[0].disabled)
	{
		FNA3D_ApplyEffect(app->renderState.device, app->assetManager.arrayShader[0].effect, 0, &stateChanges);
	}
	
	SpriteBatch_Flush(&app->renderState);
	
	FNA3D_SwapBuffers(app->renderState.device, NULL, NULL, app->renderState.window);
	
	SpriteBatch_End(&app->renderState.spriteBatch);
}

void FinalizeScreenSystem(ecs_iter_t* it)
{
	fctx();
	
	FinalizeScreenSystem_ToRTs(app);
	
	FinalizeScreenSystem_ToWindow(app);
}
