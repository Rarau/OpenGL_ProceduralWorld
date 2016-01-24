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
			


			// resets all the transformations
			glLoadIdentity();
			// set the camera transform			
			Matrix4x4 transform = _currentCamera->transform();
			Vector3 position = transform.getPosition();
			Vector3 forward = transform.forward();
			Vector3 up = transform.up();
			gluLookAt(
				position.x(),
				position.y(),
				position.z(),
				forward.x(),
				forward.y(),
				forward.z(),
				up.x(),
				up.y(),
				up.z()
				);

			//transform the entity		
			Matrix4x4 m2;
			m2.LoadIdentity();
			m2 = entity->transform();
			/*m2.Translate(entity->GetPosition().x, entity->GetPosition().y, entity->GetPosition().z);
			m2.Rotate(entity->GetRotation().x, 0.0f, 0.0f, 1.0f);
			m2.Rotate(entity->GetRotation().y, 0.0f, 1.0f, 0.0f);
			m2.Rotate(entity->GetRotation().z, 1.0f, 0.0f, 0.0f);*/

			glMultMatrixf(m2.data());


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

			entity->GetVertexBuffer()->ConfigureVertexAttributes();
			entity->GetVertexBuffer()->RenderVertexBuffer();
		}
	};
}