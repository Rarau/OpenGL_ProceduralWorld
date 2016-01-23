namespace engine
{

	class GameManager
	{
	private:

		// game logic time step
		const float Updates_Per_Second = 60.0f;
		// physics time step
		const float Physics_Updates_Per_Second = 30.0f;

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

			double p_lastTime = glfwGetTime(); //milliseconds from when we called glfwInit()			
			double p_deltaTime = 0.0f;
			
			while (_running)
			{
				double currentTime = glfwGetTime();

				// run the game logic			
				deltaTime += (currentTime - lastTime) * Updates_Per_Second;
				if (deltaTime >= 1.0f)
				{					
					_running = !glfwWindowShouldClose(_window);
					
					glfwPollEvents(); //get input events
					_playerInputSystem->Update();					

					lastTime = currentTime;
					deltaTime = 0.0f;
				}		

				// run the physics calculus
				p_deltaTime += (currentTime - p_lastTime) * Physics_Updates_Per_Second;
				if (p_deltaTime >= 1.0f)
				{					
					_movementSystem->Update(_scene->GetChildren());

					p_lastTime = currentTime;
					p_deltaTime = 0.0f;
				}

				// render the scene
				_renderSystem->Render(_scene->GetChildren());
			}
		}
	};

}