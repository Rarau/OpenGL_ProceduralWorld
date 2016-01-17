namespace engine
{
	class TerrainRenderer : public Renderer
	{

	private:

		GLuint tex;
		GLuint fbo;

	public:

		TerrainRenderer()
		{
			// Texture creation 
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

			// Now create a framebuffer object			
			glGenFramebuffers(1, &fbo);			
		}
		~TerrainRenderer()
		{

		}

		void Render(Entity* entity)
		{
			glUseProgram(entity->GetVertexBuffer()->GetShader()->GetProgramHandle());

			// set uniforms						
			glUniform1f((entity->GetVertexBuffer()->GetShader())->get_uInstanceSeparation(), 0.03f);

			// 3d texture buffer to evaluate the density function
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
			// this matrix sets our view to render properly to the 3d texture
			glLoadMatrixf(m);
			glViewport(0, 0, 33, 33);

			entity->GetVertexBuffer()->ConfigureVertexAttributes();			
			entity->GetVertexBuffer()->RenderVertexBufferInstanced(33);

			// back to the main buffer
			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			// restore the viewport
			glViewport(0.0f, 0.0f, 1280.0f, 720.0f);
		}
	};
}