#include <flecs.h>
#include "CameraFollowSystem.h"
#include "../../Application/ApplicationStateFunctions.h"

void CameraFollowSystem(ecs_iter_t* it)
{
	fctx();
	
	Body* b = ecs_column(it, Body, 1);
	CameraFollow* c = ecs_column(it, CameraFollow, 2);
	
	for(int i = 0; i < it->count; i++)
	{
		// TODO: Replace this with the Renderable's chosen RenderTarget
		app->renderState.mainRenderTarget.camera.position.X = b[i].position.X + c[i].offset.X;
		app->renderState.mainRenderTarget.camera.position.Y = b[i].position.Y + c[i].offset.Y;
	}
}
