#pragma once

namespace engine
{
	//forward declaration
	class CameraSystem;

	class RenderSystem
	{

	private:
		GLuint tex;
		GLuint fbo;

		GLFWwindow *_window;
		Entity *_currentCamera;

		RenderSystem() : _window(glfwGetCurrentContext())
		{
			// finish glew initialization
			GLint GlewInitResult = glewInit();
			if (GLEW_OK != GlewInitResult)
			{
				printf("ERROR: %s\n", glewGetErrorString(GlewInitResult));
				exit(EXIT_FAILURE);
			}			

			//Texture creation -------------------------------------------------------------------------------------------

			glGenTextures(1, &tex);
			glBindTexture(GL_TEXTURE_2D_ARRAY, tex);

			/*
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			*/
			

			glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, 33, 33, 33, 0, GL_RGBA, GL_FLOAT, NULL);

			// Now create a framebuffer object and attach the
			// 2D array texture to one of its color attachments
			glGenFramebuffers(1, &fbo);
			

			//Texture creation -------------------------------------------------------------------------------------------
		}

		~RenderSystem()
		{			
			
		}

	public:

		Entity* GetCurrentCamera()
		{
			return _currentCamera;
		}

		void SetCurrentCamera(Entity *newCamera)
		{
			_currentCamera = newCamera;
		}

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

				//glEnable(GL_NONE);
				glEnable(GL_DEPTH_TEST);


			}
			return *renderSystem;
		}

		static void DestroyRenderSystem()
		{
			RenderSystem *renderSystem = &GetRenderSystem();
			delete renderSystem;
		}

		void Render(std::vector<Entity*> *entityArray)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			for (std::vector<Entity*>::iterator iterator = entityArray->begin(); iterator != entityArray->end(); iterator++)
			{
				Entity *entity = *iterator;

				if (entity->GetVertexBuffer() != nullptr)
				{
					// If rendering terrain
					if (entity->GetType() == 1)
					{
						glUseProgram(entity->GetVertexBuffer()->GetShader()->GetProgramHandle());						

						// set uniforms						
						glUniform1f((entity->GetVertexBuffer()->GetShader())->get_uInstanceSeparation(), 0.03f);


						//3d texture buffer to evaluate the density function
						glBindFramebuffer(GL_FRAMEBUFFER, fbo);
						glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, tex, 0);
						static const GLenum draw_buffers[] =
						{
							GL_COLOR_ATTACHMENT0
						};
						glDrawBuffers(1, draw_buffers);

						glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
						

						float m[] = {
							2.0f, 0.0f, 0.0f, 0.0f,
							0.0f, 2.0f, 0.0f, 0.0f,
							0.0f, 0.0f, 2.0f, 0.0f,
							-1.0f, -1.0f, -1.0f, 1.0f,
						};
						// resets all the transformations
						glLoadIdentity();
						glLoadMatrixf(m);					


						entity->GetVertexBuffer()->ConfigureVertexAttributes();

						glViewport(0, 0, 33, 33);
						entity->GetVertexBuffer()->RenderVertexBufferInstanced(33);

						//back to the main buffer
						glBindFramebuffer(GL_FRAMEBUFFER, 0);


						glViewport(0.0f, 0.0f, 1280.0f, 720.0f);
					}
					else
					{
						GLuint textArrayIndex = entity->GetVertexBuffer()->GetShader()->get_uTextureArray();

						glUseProgram(entity->GetVertexBuffer()->GetShader()->GetProgramHandle());

						

						glUniform1i(textArrayIndex, 0);
						glActiveTexture(GL_TEXTURE0);
						glBindTexture(GL_TEXTURE_2D_ARRAY, tex);
						glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
						// resets all the transformations
						glLoadIdentity();

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

						//glScalef(entity->GetScale().x, entity->GetScale().y, entity->GetScale().z);


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
					}
				}

			}

			glfwSwapBuffers(_window);


		}
	};
}