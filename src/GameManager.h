namespace engine
{
	class GameManager
	{
	private:
		bool _running;
		GLFWwindow *_window;
		engine::RenderSystem *_renderSystem;

		VertexBuffer *vertexBuffer;

		GameManager(bool running) : _running(running), _window(glfwGetCurrentContext()), _renderSystem(&engine::RenderSystem::GetRenderSystem())
		{
			printf("GameManager created\n");
			// temporal -------------
			
			GLfloat vertices[] =
			{
				-0.5f, -0.5f, 0.0f,
				0.5f, -0.5f, 0.0f,
				0.0f, 0.5f, 0.0f,
			};
			// temporal -------------
			vertexBuffer = new VertexBuffer(vertices, sizeof(vertices), GL_TRIANGLES, 3, sizeof(GLfloat) * 3);
		}
		~GameManager()
		{
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

				printf("Running game loop\n");
				glfwPollEvents(); //get input events

				_renderSystem->Render(vertexBuffer);				
			}
		}
	};



}