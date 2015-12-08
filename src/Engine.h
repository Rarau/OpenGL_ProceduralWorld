#ifndef ENGINE_INCLUDED
#define ENGINE_INCLUDED

//#define GLFW_INCLUDE_GLU

namespace engine
{

}

#include "..\Dependencies\glew\glew.h"
#include "..\Dependencies\glfw\glfw3.h"
#include "..\Dependencies\freeglut\freeglut.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "Vector3.h"
#include "VertexData.h"

#include"CubeVertices.h"

#include "ShaderLoader.h"
#include "ShaderInterface.h"
#include "VertexBuffer.h"
#include "ResourceManager.h"
#include "RenderSystem.h"
#include "GameManager.h"

#endif