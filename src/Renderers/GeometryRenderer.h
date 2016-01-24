namespace engine
{	
	

	class GeometryRenderer : public Renderer
	{

	private:
		Entity* _currentCamera;
	public:

		GeometryRenderer(Entity* camera)
		{
			_currentCamera = camera;
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
			
			/*

				This can be set somewhere else, it's camera specific stuff, not renderer stuff

			*/
			// set the camera transform			
			Matrix4x4 transform = _currentCamera->transform();
			Vector3 position = transform.getPosition();
			Vector3 forward = transform.forward();
			Vector3 up = transform.up();
			Vector3 target = position + forward.normalized();

			Matrix4x4 viewMat;
			viewMat.Translate(position);
			viewMat.LookAt(target, up);

			
			//CameraSystem cs = CameraSystem::GetCameraSystem();
			// Build the model-view-projection matrix
			//Matrix4x4 modelViewProj = entity->transform() * viewMat * cs.GetProjectionMatrix();

			Matrix4x4 modelViewProj = entity->transform() * viewMat * GetProjectionMatrix();


			// set the color uniform
			glUniform4f((entity->GetVertexBuffer()->GetShader())->get_uColor(),
				entity->GetVertexBuffer()->GetShaderData()->Get_uColorValue().x(),
				entity->GetVertexBuffer()->GetShaderData()->Get_uColorValue().y(),
				entity->GetVertexBuffer()->GetShaderData()->Get_uColorValue().z(),
				entity->GetVertexBuffer()->GetShaderData()->Get_uColorValue().w()
				);

			glUniform3f((entity->GetVertexBuffer()->GetShader())->get_uLightPosition(),
				entity->GetVertexBuffer()->GetShaderData()->Get_uLightPosition().x(),
				entity->GetVertexBuffer()->GetShaderData()->Get_uLightPosition().y(),
				entity->GetVertexBuffer()->GetShaderData()->Get_uLightPosition().z()
				);

			// send the model-view-projection matrix to the shader
			glUniformMatrix4fv((entity->GetVertexBuffer()->GetShader())->get_uModelToProjection(), 1, GL_FALSE, modelViewProj.data());


			entity->GetVertexBuffer()->ConfigureVertexAttributes();
			entity->GetVertexBuffer()->RenderVertexBuffer();
		}
		
	};
}