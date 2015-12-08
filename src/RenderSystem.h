namespace engine
{
	class RenderSystem
	{

	private:

		GLFWwindow *_window;
		std::vector<ShaderInterface*> *shaderArray;

		RenderSystem() : _window(glfwGetCurrentContext())
		{
			// finish glew initialization
			GLint GlewInitResult = glewInit();
			if (GLEW_OK != GlewInitResult)
			{
				printf("ERROR: %s\n", glewGetErrorString(GlewInitResult));
				exit(EXIT_FAILURE);
			}

			// add shaders. TO-DO: delete this part as it is hardcoded
			shaderArray = new std::vector<ShaderInterface*>();
			ShaderInterface *shader = new ShaderInterface("Assets/Shaders/ColorVertexShader.txt", "Assets/Shaders/ColorFragmentShader.txt", "Assets/Shaders/PassThroughGeometryShader.txt");
		}

		~RenderSystem()
		{
			delete shaderArray->at(0);
			delete shaderArray;
		}

	public:

		static RenderSystem& GetRenderSystem()
		{
			static RenderSystem *renderSystem = nullptr;
			if (renderSystem == nullptr)
			{
				renderSystem = new RenderSystem();

				glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

				// set the camera projection
				glMatrixMode(GL_PROJECTION);
				// FOV, aspect ratio, near clipping plane, far clipping plane
				gluPerspective(75.0f, 1280.0f / 720.0f, 1, 1000);
				glViewport(0.0f, 0.0f, 1280.0f, 720.0f);
				glMatrixMode(GL_MODELVIEW);
			}
			return *renderSystem;
		}

		static void DestroyRenderSystem()
		{
			RenderSystem *renderSystem = &GetRenderSystem();
			delete renderSystem;
		}

		void Render(VertexBuffer *vertexBuffer)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glUseProgram(1);

			// resets all the transformations
			glLoadIdentity();
			// set the camera transform
			gluLookAt(
				0.0f, 0.0f, -5.0f, 
				0.0f, 0.0f, 0.0f, 
				0.0f, 1.0f, 0.0f
				);
			// set the color uniform
			glUniform4f(0, 1.0f, 0.0f, 0.0f, 1.0f);

			vertexBuffer->ConfigureVertexAttributes(0);
			vertexBuffer->RenderVertexBuffer();

			glfwSwapBuffers(_window);
		}
	};
}