#pragma once
#include "Renderers/TerrainRenderer.h"
namespace engine
{	
	struct ViewParameters
	{
		float FOV;
		float aspectRatio;
		float zNear;
		float zFar;
	};

	class RenderSystem
	{

	private:		

		GLFWwindow *_window;
		Entity *_currentCamera;
		ViewParameters *_viewParameters;
				
		TwBar *myBar;
		int testVar = 0;

		RenderSystem()
		{

			//OpenGL initialization code
			glfwInit();

			glfwWindowHint(GLFW_DEPTH_BITS, 24);
			glfwWindowHint(GLFW_RED_BITS, 8);
			glfwWindowHint(GLFW_GREEN_BITS, 8);
			glfwWindowHint(GLFW_BLUE_BITS, 8);
			glfwWindowHint(GLFW_ALPHA_BITS, 8);
			glfwWindowHint(GLFW_SAMPLES, 16);
			glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

			_window = glfwCreateWindow(1280, 720, "Procedural World", NULL, NULL);
			glfwMakeContextCurrent(_window);

			glEnable(GL_DEPTH_TEST);

			// Glew initialization
			GLint GlewInitResult = glewInit();
			if (GLEW_OK != GlewInitResult)
			{
				printf("ERROR: %s\n", glewGetErrorString(GlewInitResult));
				exit(EXIT_FAILURE);
			}			

			//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			glClearColor(0, 0, 0, 0);


			// set the camera projection
			
			/*
			glMatrixMode(GL_PROJECTION);
			// FOV, aspect ratio, near clipping plane, far clipping plane
			gluPerspective(45.0f, 1280.0f / 720.0f, 0.01f, 1000);
			glMatrixMode(GL_MODELVIEW);
			*/
			//glEnable(GL_NONE);
			glViewport(0.0f, 0.0f, 1280.0f, 720.0f);

			//CameraSystem::GetCameraSystem().InitViewport(45.0f, 1280.0f / 720.0f, 0.1f, 1000.0f);
			_viewParameters = new ViewParameters();
			_viewParameters->FOV = 45.0;
			_viewParameters->aspectRatio = 1280.0f / 720.0f;
			_viewParameters->zNear = 0.1f;
			_viewParameters->zFar = 1000.0f;
			
			glEnable(GL_DEPTH_TEST);

			
		}

		~RenderSystem()
		{			
			GLFWwindow *window = glfwGetCurrentContext();
			glfwDestroyWindow(window);
			glfwTerminate();
		}


	public:

		ViewParameters* GetViewParameters() const
		{
			return _viewParameters;
		}

		GLFWwindow* GetWindow()
		{
			return _window;
		}

		Entity* GetCurrentCamera()
		{
			return _currentCamera;
		}

		void SetCurrentCamera(Entity *newCamera)
		{
			_currentCamera = newCamera;
		}

		static RenderSystem& GetRenderSystem()
		{
			static RenderSystem *renderSystem = nullptr;
			if (renderSystem == nullptr)
			{
				renderSystem = new RenderSystem();				
			}
			return *renderSystem;
		}

		static void DestroyRenderSystem()
		{
			RenderSystem *renderSystem = &GetRenderSystem();
			delete renderSystem;
		}

		void Render(std::vector<Entity*> *entityArray)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		

			
			for (std::vector<Entity*>::iterator iterator = entityArray->begin(); iterator != entityArray->end(); iterator++)
			{
				Entity *entity = *iterator;
				entity->Render();				
			}
			
			UISystem::GetUISystem().Render();

			glfwSwapBuffers(_window);
		}
	};
}