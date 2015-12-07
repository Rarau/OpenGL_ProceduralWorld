namespace engine
{
	class GameManager
	{
	private:
		bool _running;
		GLFWwindow *_window;

		GameManager(bool running) : _running(running), _window(glfwGetCurrentContext())
		{
			printf("GameManager created\n");
		}
		~GameManager()
		{
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
				printf("Running game loop\n");

				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				_running = !glfwWindowShouldClose(_window);

				glfwSwapBuffers(_window);
				glfwPollEvents();
			}
		}
	};



}