namespace engine
{
	class RenderSystem
	{

	private:

		GLFWwindow *_window;	

		CameraSystem *_cameraSystem;
		Entity *_currentCamera;

		RenderSystem() : _window(glfwGetCurrentContext()), _cameraSystem(&CameraSystem::GetCameraSystem())
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
				glEnable(GL_DEPTH_TEST);
			}
			return *renderSystem;
		}

		static void DestroyRenderSystem()
		{
			RenderSystem *renderSystem = &GetRenderSystem();
			delete renderSystem;
		}

		void Render(Entity *entity)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glUseProgram(entity->GetVertexBuffer()->GetShader()->GetProgramHandle());

			// resets all the transformations
			glLoadIdentity();

			_currentCamera = _cameraSystem->GetCurrentCamera();
			// set the camera transform
			gluLookAt(
				_currentCamera->GetPosition().x,
				_currentCamera->GetPosition().y,
				_currentCamera->GetPosition().z,
				_currentCamera->GetEyeVector().x,
				_currentCamera->GetEyeVector().y,
				_currentCamera->GetEyeVector().z,
				_currentCamera->GetUpVector().x,
				_currentCamera->GetUpVector().y,
				_currentCamera->GetUpVector().z
				);

			//transform the entity			
			glTranslatef(entity->GetPosition().x, entity->GetPosition().y, entity->GetPosition().z);

			glRotatef(entity->GetRotation().x, 0.0f, 0.0f, 1.0f);
			glRotatef(entity->GetRotation().y, 0.0f, 1.0f, 0.0f);
			glRotatef(entity->GetRotation().z, 1.0f, 0.0f, 0.0f);

			glScalef(entity->GetScale().x, entity->GetScale().y, entity->GetScale().z);


			// set the color uniform
			glUniform4f((entity->GetVertexBuffer()->GetShader())->get_uColor(),
				entity->GetVertexBuffer()->GetShaderData()->Get_uColorValue().x,
				entity->GetVertexBuffer()->GetShaderData()->Get_uColorValue().y,
				entity->GetVertexBuffer()->GetShaderData()->Get_uColorValue().z,
				entity->GetVertexBuffer()->GetShaderData()->Get_uColorValue().w
				);

			glUniform3f((entity->GetVertexBuffer()->GetShader())->get_uLightPosition(),
				entity->GetVertexBuffer()->GetShaderData()->Get_uLightPosition().x,
				entity->GetVertexBuffer()->GetShaderData()->Get_uLightPosition().y,
				entity->GetVertexBuffer()->GetShaderData()->Get_uLightPosition().z
				);

			entity->GetVertexBuffer()->ConfigureVertexAttributes();
			entity->GetVertexBuffer()->RenderVertexBuffer();

			glfwSwapBuffers(_window);
		}
	};
}