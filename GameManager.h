namespace engine
{
	class GameManager
	{
	private:
		GameManager()
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
				glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
				glutInitWindowPosition(500, 500);
				glutInitWindowSize(800, 600);
				int window = glutCreateWindow("OpenGL First Window");
				glutSetWindow(window);				
				glEnable(GL_DEPTH_TEST);
				
				
				gameManager = new GameManager();
			}
			return *gameManager;
		}

		static void DestroyGameManager()
		{
			GameManager *gameManager = &(GetGameManager());
			if (gameManager != nullptr)
			{
				int window = glutGetWindow();
				glutDestroyWindow(window);
				delete gameManager;
			}
		}
		
	};



}