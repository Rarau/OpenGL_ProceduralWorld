namespace engine
{	

	class GeometryRenderer : public Renderer
	{

	private:

	public:

		GeometryRenderer()
		{
			
		}
		~GeometryRenderer()
		{

		}

		void Render(Entity* entity)
		{
			// In this renderer, we need the entity's geometry
			if (entity->GetVertexBuffer() == nullptr) return;

			GLuint textArrayIndex = entity->GetVertexBuffer()->GetShader()->get_uTextureArray();

			glUseProgram(entity->GetVertexBuffer()->GetShader()->GetProgramHandle());

			//TO-DO: this is part of the terrain renderer, get it out of here! -----------------------------
			glUniform1i(textArrayIndex, 0);
			glActiveTexture(GL_TEXTURE0);
			//glBindTexture(GL_TEXTURE_2D_ARRAY, tex);
			glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			//-----------------------------------------------------------------------------------------------
			
			// resets all the transformations
			glLoadIdentity();
			// set the camera transform	
			Entity *_currentCamera = RenderSystem::GetRenderSystem().GetCurrentCamera();
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
	};
}