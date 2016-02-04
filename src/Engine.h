#ifndef ENGINE_INCLUDED
#define ENGINE_INCLUDED

//#define GLFW_INCLUDE_GLU

namespace engine
{

}

#include "..\Dependencies\glew\glew.h"
#include "..\Dependencies\glfw\glfw3.h"
#include "..\Dependencies\freeglut\freeglut.h"
#include "..\Dependencies\AntTweakBar\AntTweakBar.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>

#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4x4.h"

#include "MatrixVector4Glue.h"

#include "VertexData.h"
#include "ShaderData.h"

#include "CubeVertices.h"
#include "Tables.h"

#include "Renderer.h"
#include "ShaderLoader.h"
#include "ShaderInterface.h"
#include "VertexBuffer.h"
#include "Entity.h"


#include "PlayerInputSystem.h"
#include "MovementSystem.h"
#include "Renderers/TerrainRenderer.h"
#include "Renderers/GeometryRenderer.h"
#include "ResourceManager.h"
#include "RenderSystem.h"
#include "CameraSystem.h"
#include "RendererAux.h"

#include "Scene.h"
#include "Terrain.h"
#include "GameManager.h"

#endif