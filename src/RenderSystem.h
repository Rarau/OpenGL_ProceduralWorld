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

			
		}

		~RenderSystem()
		{			
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

				glEnable(GL_CULL_FACE);
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

			glUseProgram(vertexBuffer->GetShader()->GetProgramHandle());

			// resets all the transformations
			glLoadIdentity();
			// set the camera transform
			gluLookAt(
				3.0f, 2.0f, -2.0f, //position of the camera
				0.0f, 0.0f, 0.0f,  //where are we looking at
				0.0f, 1.0f, 0.0f
				);
			// set the color uniform
			glUniform4f(0, 1.0f, 0.0f, 0.0f, 1.0f);

			vertexBuffer->ConfigureVertexAttributes();
			vertexBuffer->RenderVertexBuffer();

			glfwSwapBuffers(_window);
		}
	};
}