namespace engine
{
	class PlayerInputSystem
	{

	private:

		Entity *_currentPlayer;
		GLFWwindow *_window;
		double mouseX;
		double mouseY;
		double prevMouseX;
		double prevMouseY;

		PlayerInputSystem() : _window(glfwGetCurrentContext())
		{
			mouseX = mouseY = prevMouseX = prevMouseY = 0.0;
		}

		~PlayerInputSystem()
		{

		}

		void keyCallBack(GLFWwindow *window, int key, int scancode, int action, int mods)
		{
			//std::cout << "test" << std::endl;
			if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			{
				if (glfwGetInputMode(glfwGetCurrentContext(), GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
				{
					// re-enable the cursor on "escape" key press
					glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				}
				else
				{
					glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				}
			}
			TwEventKeyGLFW(key, action);
		}

		void mouseCallBack(GLFWwindow *window, int button, int action, int mods) {
			// Notify AntTweakBar about button events
			TwEventMouseButtonGLFW(button, action);
		}

	public:

		void SetCurrentPlayer(Entity *newPlayer)
		{
			_currentPlayer = newPlayer;			
		}

		void Update()
		{
			glfwGetCursorPos(_window, &mouseX, &mouseY);
			TwMouseMotion(mouseX, mouseY);
			// TO-DO: We should call the entity setVelocity() method instead of moving directly.
			if (_currentPlayer != nullptr && glfwGetInputMode(glfwGetCurrentContext(), GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
			{

				if (glfwGetKey(_window, GLFW_KEY_W))
				{
					_currentPlayer->transform().Translate(_currentPlayer->transform().forward() * 0.03f);
				}
				if (glfwGetKey(_window, GLFW_KEY_S))
				{
					_currentPlayer->transform().Translate(_currentPlayer->transform().forward() * -0.03f);
				}
				if (glfwGetKey(_window, GLFW_KEY_A))
				{
					_currentPlayer->transform().Translate(_currentPlayer->transform().right() * 0.03f);
				}
				if (glfwGetKey(_window, GLFW_KEY_D))
				{
					_currentPlayer->transform().Translate(_currentPlayer->transform().right() * -0.03f);
				}
				if (glfwGetKey(_window, GLFW_KEY_Q))
				{
					_currentPlayer->transform().Translate(_currentPlayer->transform().up() * 0.03f);
				}
				if (glfwGetKey(_window, GLFW_KEY_E))
				{
					_currentPlayer->transform().Translate(_currentPlayer->transform().up() * -0.03f);
				}
				if (glfwGetKey(_window, GLFW_KEY_N))
				{
					_currentPlayer->transform().Rotate(2.0f, 0.0f, 1.0f, 0.0f);
				}
				if (glfwGetKey(_window, GLFW_KEY_M))
				{
					_currentPlayer->transform().Rotate(-2.0f, 0.0f, 1.0f, 0.0f);
				}
				
				//_currentPlayer->transform().Rotate(-0.1f * (mouseX - prevMouseX), 0.0f, 1.0f, 0.0f);
				Vector3 playerRight = Vector4(1.0f, 0.0f, 0.0f, 0.0f) * _currentPlayer->transform().Inverse();
				Vector3 playerUp = Vector4(0.0f, 1.0f, 0.0f, 0.0f) * _currentPlayer->transform().Inverse();

				_currentPlayer->transform().Rotate(0.1f * (mouseX - prevMouseX), playerUp.x(), playerUp.y(), playerUp.z());
				//_currentPlayer->transform().Rotate(-0.1f * (mouseY - prevMouseY), playerRight.x(), playerRight.y(), playerRight.z());

				_currentPlayer->transform().Rotate(0.1f * (mouseY - prevMouseY), 1.0f, 0.0f, 0.0f);

				prevMouseX = mouseX;
				prevMouseY = mouseY;
			}
		}

		//TO-DO: manage all keys with events and delete the update function
		// actions: onPress, onRelease... mods: alt, shift...
		static void keyCallBackFun(GLFWwindow *window, int key, int scancode, int action, int mods)
		{
			PlayerInputSystem *playerInputSystem = &GetPlayerInputSystem();
			playerInputSystem->keyCallBack(window, key, scancode, action, mods);
		}

		static void mouseCallBackFun(GLFWwindow *window, int button, int action, int mods)
		{
			PlayerInputSystem *playerInputSystem = &GetPlayerInputSystem();
			playerInputSystem->mouseCallBack(window, button, action, mods);
		}

		static void charCallBackFun(GLFWwindow *window, int character)
		{
			TwEventCharGLFW(character, 1);
		}

		static PlayerInputSystem& GetPlayerInputSystem()
		{
			static PlayerInputSystem *playerInputSystem = nullptr;
			if (playerInputSystem == nullptr)
			{
				GLFWwindow *window = glfwGetCurrentContext();
				// bind the keyPress to our static function
				glfwSetKeyCallback(window, *keyCallBackFun);

				glfwSetMouseButtonCallback(window, *mouseCallBackFun);

				// disable the cursor
				glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

				playerInputSystem = new PlayerInputSystem();
			}
			return *playerInputSystem;
		}

		static void DestroyInputSystem()
		{
			PlayerInputSystem *playerInputSystem = &GetPlayerInputSystem();
			delete playerInputSystem;
		}

	};
}