namespace engine
{
#define Updates_Per_Second 60.0f

	class GameManager
	{
	private:

		bool _running;
		GLFWwindow *_window;

		engine::RenderSystem *_renderSystem;
		engine::ResourceManager *_resourceManager;
		engine::MovementSystem *_movementSystem;	
		engine::CameraSystem *_cameraSystem;	
		engine::PlayerInputSystem *_playerInputSystem;

		Scene *_scene;

		GameManager(bool running) : _running(running), _window(glfwGetCurrentContext()), 
			_renderSystem(&engine::RenderSystem::GetRenderSystem()), 
			_resourceManager(&ResourceManager::GetResourceManager()), 
			_movementSystem(&MovementSystem::GetMovementSystem()),
			_cameraSystem(&CameraSystem::GetCameraSystem()),
			_playerInputSystem(&PlayerInputSystem::GetPlayerInputSystem())
		{
			printf("GameManager created\n");

			_scene = new Scene();
		}

		~GameManager()
		{
			engine::ResourceManager::DestroyResourceManager();
			engine::RenderSystem::DestroyRenderSystem();	
			engine::CameraSystem::DestroyCameraSystem();
			engine::PlayerInputSystem::DestroyInputSystem();

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
				glfwWindowHint(GLFW_SAMPLES, 16);
				glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

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
			double lastTime = glfwGetTime(); //milliseconds from when we called glfwInit()
			double deltaTime = 0.0f;			

			while (_running)
			{
				double currentTime = glfwGetTime();
				deltaTime += (currentTime - lastTime) * Updates_Per_Second;

				if (deltaTime >= 1.0f)
				{
					//printf("Running game loop\n");
					_running = !glfwWindowShouldClose(_window);
					
					glfwPollEvents(); //get input events

					_playerInputSystem->Update();
					_movementSystem->Update(_scene->GetChildren());

					deltaTime = 0.0f;
				}				

				//TO-DO: we are rendering a concrete entity, not all
				_renderSystem->Render(_scene->GetChildren());
			}
		}
	};



}