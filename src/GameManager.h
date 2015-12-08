namespace engine
{
	class GameManager
	{
	private:
		bool _running;
		GLFWwindow *_window;
		engine::RenderSystem *_renderSystem;
		engine::ResourceManager *_resourceManager;

		VertexBuffer *vertexBuffer;

		GameManager(bool running) : _running(running), _window(glfwGetCurrentContext()), 
		_renderSystem(&engine::RenderSystem::GetRenderSystem()), _resourceManager(&ResourceManager::GetResourceManager())
		{
			printf("GameManager created\n");			
		}
		~GameManager()
		{
			engine::ResourceManager::DestroyResourceManager();
			engine::RenderSystem::DestroyRenderSystem();			
			printf("GameManager destroyed\n");
		}
	public:
		//Singleton implementation
		static GameManager& GetGameManager()
		{
			static GameManager *gameManager = nullptr;

			if (gameManager == nullptr)
			{
				//OpenGL initialization code
				glfwInit();				

				glfwWindowHint(GLFW_DEPTH_BITS, 24);
				glfwWindowHint(GLFW_RED_BITS, 8);
				glfwWindowHint(GLFW_GREEN_BITS, 8);
				glfwWindowHint(GLFW_BLUE_BITS, 8);
				glfwWindowHint(GLFW_ALPHA_BITS, 8);

				GLFWwindow *window = glfwCreateWindow(1280, 720, "Procedural World", NULL, NULL);
				glfwMakeContextCurrent(window);

				glEnable(GL_DEPTH_TEST);

				gameManager = new GameManager(true);
			}
			return *gameManager;
		}

		static void DestroyGameManager()
		{
			GameManager *gameManager = &(GetGameManager());
			delete gameManager;
			GLFWwindow *window = glfwGetCurrentContext();
			glfwDestroyWindow(window);
			glfwTerminate();
		}

		void RunGameLoop()
		{
			while (_running)
			{
				_running = !glfwWindowShouldClose(_window);

				//printf("Running game loop\n");
				glfwPollEvents(); //get input events

				//TO-DO: we are rendering a concrete vertex buffer, not all
				_renderSystem->Render((_resourceManager->GetVertexBufferArray())->at(0));				
			}
		}
	};



}