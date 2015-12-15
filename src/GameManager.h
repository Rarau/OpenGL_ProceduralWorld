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

		Entity *_entity;
		Entity *_camera;

		VertexBuffer *vertexBuffer;

		GameManager(bool running) : _running(running), _window(glfwGetCurrentContext()), 
			_renderSystem(&engine::RenderSystem::GetRenderSystem()), 
			_resourceManager(&ResourceManager::GetResourceManager()), 
			_movementSystem(&MovementSystem::GetMovementSystem()),
			_cameraSystem(&CameraSystem::GetCameraSystem())
		{
			printf("GameManager created\n");	

			//TO-DO: this is hardcoded, can't be here
			_camera = new Entity(nullptr, MakeVector3(2.0f, 2.0f, 4.0f));
			_camera->SetEyeVector(MakeVector3(0.0f, 0.0f, 0.0f));
			_cameraSystem->SetCurrentCamera(_camera);

			_entity = new Entity(_resourceManager->GetVertexBufferArray()->at(0), MakeVector3(0.0f, 0.0f, 0.0f));
			_entity->SetRotation(MakeVector3(30.0f, 0.0f, 0.0f));
			_entity->SetScale(MakeVector3(2.0f, 2.0f, 2.0f));
			_entity->SetRotationVelocity(MakeVector3(0.3f, 0.0f, 0.0f));

		}
		~GameManager()
		{
			engine::ResourceManager::DestroyResourceManager();
			engine::RenderSystem::DestroyRenderSystem();	
			engine::CameraSystem::DestroyCameraSystem();
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

					_movementSystem->Update(_entity);
					deltaTime = 0.0f;
				}				

				//TO-DO: we are rendering a concrete entity, not all
				_renderSystem->Render(_entity);				
			}
		}
	};



}