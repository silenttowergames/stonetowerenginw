#include <flecs.h>
#include "MoveSystem.h"
#include "../FlecsMapFunctions.h"
#include "../../Application/ApplicationState.h"
#include "../Components/AIPlayer.h"
#include "../Components/BasicAABB.h"
#include "../Components/Body.h"
#include "../../Audio/SoundFunctions.h"
#include "../../Application/ConfigFunctions.h"
#include "../../Application/ApplicationStateFunctions.h"
#include "../../Input/GamepadStateFunctions.h"
#include "../../Input/KeyboardStateFunctions.h"
#include "../../Input/MouseStateFunctions.h"
#include "../../Utilities/wallsFunctions.h"

void MoveSystem(ecs_iter_t* it)
{
	fctx();
	
	ECS_COMPONENT(it->world, BasicAABB);
	
	AIPlayer* a = ecs_column(it, AIPlayer, 1);
	Body* b = ecs_column(it, Body, 2);
	
	for(int i = 0; i < it->count; i++)
	{
		memset(&b[i].velocity, 0, sizeof(float2d));
		
		if(key(Down, RIGHT) || button(Down, 0, DPAD_RIGHT) || button(Down, 1, STICK_RIGHT_RIGHT) || axis(0, STICK_LEFT_DOWN) >= 0.9f)
		{
			b[i].velocity.X += a[i].speed;
		}
		
		if(key(Down, LEFT) || button(Down, 0, DPAD_LEFT) || button(Down, 0, STICK_RIGHT_LEFT) || button(Released, 0, STICK_LEFT_RIGHT))
		{
			b[i].velocity.X -= a[i].speed;
		}
		
		if(key(Down, DOWN) || button(Down, 0, DPAD_DOWN) || button(Down, 0, STICK_RIGHT_DOWN))
		{
			b[i].velocity.Y += a[i].speed;
		}
		
		if(key(Down, UP) || button(Down, 0, DPAD_UP) || button(Down, 0, STICK_RIGHT_UP))
		{
			b[i].velocity.Y -= a[i].speed;
		}
		
		if(button(Down, 0, X))
		{
			rumble(0, 1.0f, 500);
		}
		
		if(mouse(Pressed, LEFTCLICK))
		{
			b[i].velocity.X += 16;
		}
		
		if(mouse(Down, RIGHTCLICK))
		{
			b[i].velocity.Y++;
		}
		
		if(mouse(Pressed, MIDDLECLICK))
		{
			b[i].velocity.Y += 16;
		}
	}
	
	if(
		(key(Down, LALT) && key(Pressed, RETURN))
		||
		(key(Down, LCTRL) && key(Pressed, f))
	)
	{
		if(app->config.fullscreen)
		{
			Config_Resize(app, 1280, 720, false);
		}
		else
		{
			Config_Resize(app, -1, -1, true);
		}
	}
	
	if(key(Pressed, x))
	{
		Sound_play(*mapGet(app->assetManager.mapSound, "calm-example.ogg", Sound*), app->assetManager.audioManager.soloud);
	}
	
	if(key(Pressed, z))
	{
		Sound_play(*mapGet(app->assetManager.mapSound, "speech0", Sound*), app->assetManager.audioManager.soloud);
	}
	
	if(key(Pressed, c))
	{
		Sound_play(*mapGet(app->assetManager.mapSound, "hit.ogg", Sound*), app->assetManager.audioManager.soloud);
	}
}
