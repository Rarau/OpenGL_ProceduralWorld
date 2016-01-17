namespace engine
{

	class GameManager
	{
	private:

		// game simulation time step
		const float Updates_Per_Second = 60.0f;

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
			_window = _renderSystem->GetWindow();
			_scene = new Scene();
		}

		~GameManager()
		{			
			engine::RenderSystem::DestroyRenderSystem();
			engine::ResourceManager::DestroyResourceManager();
			engine::MovementSystem::DestroyMovementSystem();
			engine::CameraSystem::DestroyCameraSystem();
			engine::PlayerInputSystem::DestroyInputSystem();

			printf("GameManager destroyed\n");
		}
	public:
		// Singleton implementation
		static GameManager& GetGameManager()
		{
			static GameManager *gameManager = nullptr;

			if (gameManager == nullptr)
			{
				gameManager = new GameManager(true);
			}
			return *gameManager;
		}

		static void DestroyGameManager()
		{
			GameManager *gameManager = &(GetGameManager());
			delete gameManager;			
		}

		void RunGameLoop()
		{
			double lastTime = glfwGetTime(); //milliseconds from when we called glfwInit()
			double deltaTime = 0.0f;			

			while (_running)
			{
				// run the game simulation at a defined frequency
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

				// render the scenes as many times as possible
				_renderSystem->Render(_scene->GetChildren());
			}
		}
	};

}