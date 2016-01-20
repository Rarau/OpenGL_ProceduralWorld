namespace engine
{
	class PlayerInputSystem
	{

	private:

		Vector3 _eyeVector;

		Entity *_currentPlayer;
		GLFWwindow *_window;

		PlayerInputSystem() : _window(glfwGetCurrentContext())
		{

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
		}

	public:

		void SetCurrentPlayer(Entity *newPlayer)
		{
			_currentPlayer = newPlayer;
			_eyeVector = NormalizeVector3(newPlayer->GetEyeVector());
		}

		void Update()
		{
			// TO-DO: We should call the entity setVelocity() method instead of moving directly.
			if (_currentPlayer != nullptr && glfwGetInputMode(glfwGetCurrentContext(), GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
			{
				if (glfwGetKey(_window, GLFW_KEY_W))
				{
					_currentPlayer->SetPosition(AddVector3(_currentPlayer->GetPosition(), scalarMultiplyVector3(_eyeVector, 0.03f)));					
				}
				if (glfwGetKey(_window, GLFW_KEY_S))
				{
					_currentPlayer->SetPosition(SubstractVector3(_currentPlayer->GetPosition(), scalarMultiplyVector3(_eyeVector, 0.03f)));
				}
				if (glfwGetKey(_window, GLFW_KEY_A))
				{
					_currentPlayer->SetPosition(SubstractVector3(_currentPlayer->GetPosition(), scalarMultiplyVector3(_currentPlayer->GetRightVector(), -0.03f)));
				}
				if (glfwGetKey(_window, GLFW_KEY_D))
				{
					_currentPlayer->SetPosition(SubstractVector3(_currentPlayer->GetPosition(), scalarMultiplyVector3(_currentPlayer->GetRightVector(), 0.03f)));
				}
				if (glfwGetKey(_window, GLFW_KEY_Q))
				{
					_currentPlayer->SetPosition(AddVector3(_currentPlayer->GetPosition(), scalarMultiplyVector3(MakeVector3(0.0f, 1.0f, 0.0f), 0.03f)));
				}
				if (glfwGetKey(_window, GLFW_KEY_E))
				{
					_currentPlayer->SetPosition(SubstractVector3(_currentPlayer->GetPosition(), scalarMultiplyVector3(MakeVector3(0.0f, 1.0f, 0.0f), 0.03f)));
				}
				_currentPlayer->SetEyeVector(AddVector3(_currentPlayer->GetPosition(), _eyeVector));
			}
		}

		//TO-DO: manage all keys with events and delete the update function
		// actions: onPress, onRelease... mods: alt, shift...
		static void keyCallBackFun(GLFWwindow *window, int key, int scancode, int action, int mods)
		{
			PlayerInputSystem *playerInputSystem = &GetPlayerInputSystem();
			playerInputSystem->keyCallBack(window, key, scancode, action, mods);
		}

		static PlayerInputSystem& GetPlayerInputSystem()
		{
			static PlayerInputSystem *playerInputSystem = nullptr;
			if (playerInputSystem == nullptr)
			{
				// bind the keyPress to our static function
				glfwSetKeyCallback(glfwGetCurrentContext(), *keyCallBackFun);
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