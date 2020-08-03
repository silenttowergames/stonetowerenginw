// Stone Tower Engine
// Silent Tower Games LLC

// OS
// Windows
#ifdef _WIN32
#include <windows.h>
#endif

// Dependencies
// MojoShader
#define MOJOSHADER_NO_VERSION_INCLUDE
#define MOJOSHADER_EFFECT_SUPPORT
#include <mojoshader.h>
#include <mojoshader_effects.h>
// SDL
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
// FNA3D
#include <FNA3D.h>
// C standards
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// Flecs
#include <flecs.h>
// SoLoud
#define WITH_SDL2
#include <soloud_c.h>
// JSON-C
#include <json.h>

// Vendor
// STB Image
#define STB_IMAGE_IMPLEMENTATION
#ifdef __MINGW32__
#define STBI_NO_THREAD_LOCALS
#endif
#include "vendor/stb_image.h"
// FontStash
#define FONTSTASH_IMPLEMENTATION
#include "vendor/fontstash/fontstash.h"

// ===

// Engine Code
// Application
#include "Application/ApplicationState.h"
#include "Application/ApplicationStateFunctions.c"

// Assets
#include "Assets/Shader.h"
#include "Assets/ShaderFunctions.c"
#include "Assets/Texture.h"
#include "Assets/TextureFunctions.c"

// ECS
// Systems
#include "ECS/Systems/DrawSystem.c"
#include "ECS/Systems/SDLEventsSystem.c"
#include "ECS/Systems/SystemPrintHelloWorld.c"
#include "ECS/Systems/Test1System.c"
#include "ECS/Systems/Test2System.c"
#include "ECS/Systems/Test3System.c"
// .
#include "ECS/FlecsFunctions.c"

// Logger
#include "Logging/Logger.h"
#include "Logging/LoggerFunctions.c"

// Rendering
#include "Rendering/Camera.h"
#include "Rendering/CameraFunctions.c"
#include "Rendering/Matrix.h"
#include "Rendering/MatrixFunctions.c"
#include "Rendering/RenderingFunctions.c"
#include "Rendering/RenderState.h"
#include "Rendering/RenderStateFunctions.c"
#include "Rendering/SpriteBatch.h"
#include "Rendering/SpriteBatchFunctions.c"

// Utilities
#include "Utilities/float2d.h"
#include "Utilities/float4d.h"
#include "Utilities/int2d.h"
#include "Utilities/Map.h"
#include "Utilities/MapFunctions.c"
#include "Utilities/quad.h"
#include "Utilities/quadFunctions.c"
