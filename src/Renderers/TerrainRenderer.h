namespace engine
{
	// Vertices for the evaluator quads
	// TO-DO: this quad should apply the block's transformations
	VertexDataP quadEvaluatorVertices[] = {
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f },

		{ 0.0f, 1.0f, 0.0f },
		{ 1.0f, 1.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f }
	};

	// Auxiliar function to generate the block sampling vertices
	VertexDataP* GenerateSamplingVertices()
	{
		VertexDataP verts[32 * 32 * 32];
		for (int x = 0; x < 32; x++)
		{
			for (int y = 0; y < 32; y++)
			{
				for (int z = 0; z < 32; z++)
				{
					verts[32 * 32 * z + 32 * y + x] = { (float)x / 32.0f, (float)y / 32.0f, (float)z / 32.0f };
				}
			}
		}
		return verts;
	}

	class TerrainRenderer : public Renderer
	{

	private:

		GLuint _quadVertexBufferID;

		ShaderInterface *_functionEvaluatorShader;
		GLint _aPositionVertex;
		GLuint _uInstanceSeparation;

		GLuint textureId;
		GLuint frameBufferObjectId;

		GLuint _blockVertexBufferID;
		VertexDataP *_blockVertices;

		ShaderInterface *_blockShader;	


	public:

		TerrainRenderer()
		{
			// Create hard-coded the quad vertex buffer
			glGenBuffers(1, &_quadVertexBufferID);
			glBindBuffer(GL_ARRAY_BUFFER, _quadVertexBufferID);
			glBufferData(GL_ARRAY_BUFFER, sizeof(quadEvaluatorVertices), quadEvaluatorVertices, GL_STATIC_DRAW);

			// Create hard-coded the block vertex buffer
			_blockVertices = GenerateSamplingVertices();
			glGenBuffers(1, &_blockVertexBufferID);
			glBindBuffer(GL_ARRAY_BUFFER, _blockVertexBufferID);
			glBufferData(GL_ARRAY_BUFFER, sizeof(VertexDataP) * 32 * 32 * 32, _blockVertices, GL_STATIC_DRAW);
			
			// Create Instanced Rendering evaluator shader
			_functionEvaluatorShader = new ShaderInterface("Assets/Shaders/InstancedVertexShader.glsl",
				"Assets/Shaders/InstancedFragmentShader.glsl",
				"Assets/Shaders/InstancedGeometryShader.glsl");

			// Create block shader
			_blockShader = new ShaderInterface("Assets/Shaders/BlockVertexShader.glsl",
				"Assets/Shaders/BlockFragmentShader.glsl", 
				"Assets/Shaders/BlockGeometryShader.glsl");

			// Create texture 3D 
			glGenTextures(1, &textureId);
			glBindTexture(GL_TEXTURE_2D_ARRAY, textureId);
			/*
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			*/
			glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, 33, 33, 33, 0, GL_RGBA, GL_FLOAT, NULL);

			// Create a framebuffer object			
			glGenFramebuffers(1, &frameBufferObjectId);			
		}
		~TerrainRenderer()
		{

		}

		void Render(Entity* entity)
		{
			// FIRST PASS - Sample density function in a 3D texture

			// select shader program
			glUseProgram(_functionEvaluatorShader->GetProgramHandle());

			// set uniforms						
			// TO-DO: hardcoded 0.03, it should be the block side length/32
			glUniform1f(_functionEvaluatorShader->get_uInstanceSeparation(), 0.03f);

			// bind 3d texture buffer
			glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObjectId);
			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureId, 0);
			static const GLenum draw_buffers[] =
			{
				GL_COLOR_ATTACHMENT0
			};
			glDrawBuffers(1, draw_buffers);

			// clear the texture buffer
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// configure our camera and viewport to render properly to the 3d texture
			float m[] = {
				2.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 2.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 2.0f, 0.0f,
				-1.0f, -1.0f, -1.0f, 1.0f,
			};			
			glLoadIdentity();			
			glLoadMatrixf(m);
			glViewport(0, 0, 33, 33);

			// enable quad vertex buffer
			glBindBuffer(GL_ARRAY_BUFFER, _quadVertexBufferID);
			glEnableVertexAttribArray(_functionEvaluatorShader->Get_aPositionVertex());
			glVertexAttribPointer(_functionEvaluatorShader->Get_aPositionVertex(), 3, GL_FLOAT, GL_FALSE, sizeof(VertexDataP), 0);

			// execute sampler shader
			glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 33);

			// SECOND PASS - Create geometry for each voxel (32x32x32 in the block)

			// get back to the main buffer
			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			// restore the viewport
			glViewport(0.0f, 0.0f, 1280.0f, 720.0f);

			glUseProgram(_blockShader->GetProgramHandle());
			
			//glUniform1i(textArrayIndex, 0);
			glActiveTexture(GL_TEXTURE0);
			//glBindTexture(GL_TEXTURE_2D_ARRAY, textureId);
			glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

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

			// enable block vertex buffer
			glBindBuffer(GL_ARRAY_BUFFER, _blockVertexBufferID);			
			glEnableVertexAttribArray(_blockShader->Get_aPositionVertex());
			glVertexAttribPointer(_blockShader->Get_aPositionVertex(), 3, GL_FLOAT, GL_FALSE, sizeof(VertexDataP), 0);
			
			// execute drawing shader
			glDrawArrays(GL_POINTS, 0, 33 * 33 * 33);
		}
	};
}