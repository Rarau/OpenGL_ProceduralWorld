#pragma once

namespace engine
{
	
	// Vertices for the evaluator quads
	// TO-DO: this quad should apply the block's transformations
	Vector3 quadEvaluatorVertices[] = {
		Vector3( 0.0f, 0.0f, 0.0f ),
		Vector3( 0.0f, 1.0f, 0.0f ),
		Vector3( 1.0f, 0.0f, 0.0f ),

		Vector3( 0.0f, 1.0f, 0.0f ),
		Vector3( 1.0f, 1.0f, 0.0f ),
		Vector3( 1.0f, 0.0f, 0.0f )
	};

	// Auxiliar function to generate the block sampling vertices
	Vector3* GenerateSamplingVertices()
	{
		Vector3 verts[32 * 32 * 33];
		for (int x = 0; x < 32; x++)
		{
			for (int y = 0; y < 32; y++)
			{
				for (int z = 0; z < 33; z++)
				{
					verts[32 * 32 * z + 32 * y + x] = Vector3( (float)x / 32.0f, (float)y / 32.0f, (float)z / 32.0f );
				}
			}
		}
		return verts;
	}

	struct shader_edge_table
	{
		GLint table[3840];
	};

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
		Vector3*_blockVertices;

		ShaderInterface *_blockShader;	

		GLuint ubo = 0;		
		shader_edge_table edge_table;

		Entity* _currentCamera;

		float time;

	public:

		TerrainRenderer(Entity* camera)
		{
			time = 0.0f;

			_currentCamera = camera;

			// Create hard-coded the quad vertex buffer
			glGenBuffers(1, &_quadVertexBufferID);
			glBindBuffer(GL_ARRAY_BUFFER, _quadVertexBufferID);
			glBufferData(GL_ARRAY_BUFFER, sizeof(quadEvaluatorVertices), quadEvaluatorVertices, GL_STATIC_DRAW);

			//glUniformBlockBinding​(GLuint program​, GLuint uniformBlockIndex​, GLuint uniformBlockBinding​);

			// Create hard-coded the block vertex buffer
			_blockVertices = GenerateSamplingVertices();
			glGenBuffers(1, &_blockVertexBufferID);
			glBindBuffer(GL_ARRAY_BUFFER, _blockVertexBufferID);
			glBufferData(GL_ARRAY_BUFFER, sizeof(VertexDataP) * 32 * 32 * 32, _blockVertices, GL_STATIC_DRAW);
			
			// Create Instanced Rendering evaluator shader
			_functionEvaluatorShader = new ShaderInterface(
				"Assets/Shaders/InstancedVertexShader.glsl",
				"Assets/Shaders/InstancedFragmentShader.glsl",
				"Assets/Shaders/InstancedGeometryShader.glsl");

			// Create block shader
			_blockShader = new ShaderInterface(
				"Assets/Shaders/BlockVertexShader.glsl",
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
			glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_R32F, 33, 33, 33, 0, GL_RED, GL_FLOAT, NULL);

			// Create a framebuffer object			
			glGenFramebuffers(1, &frameBufferObjectId);		


			// Create uniform buffer
			for (int i = 0; i < 3840; i++)
			{
				edge_table.table[i] = edge_connect_list[i];
			}

			ubo = 0;
			//glGenBuffers(1, &ubo);
			//glBindBuffer(GL_UNIFORM_BUFFER, ubo);
			//glBufferData(GL_UNIFORM_BUFFER, sizeof(edge_table), &(edge_table), GL_STATIC_DRAW);
			////this line is causing problems
			//glBindBufferRange(GL_UNIFORM_BUFFER, 0, ubo, 0, sizeof(edge_table.table)); // this binds UBO to Buffer Index

			glGenBuffers(1, &ubo);
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, ubo);
			glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(edge_table), &(edge_table), GL_STATIC_DRAW);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ubo);

			
		}
		~TerrainRenderer()
		{

		}

		void Render(Entity* entity)
		{
			time += 1.0f / 33.0f;

			for (int k = -1; k < 1; k++)
			{
				for (int j = -2; j < 2; j++)
				{
					for (int i = -2; i < 2; i++)
					{

						// FIRST PASS - Sample density function in a 3D texture

						// select shader program
						glUseProgram(_functionEvaluatorShader->GetProgramHandle());

						// set uniforms						
						// TO-DO: hardcoded 0.03, it should be the block side length/32
						glUniform1f(_functionEvaluatorShader->get_uInstanceSeparation(), 0.03f);
						glUniform1f(6, time);

						// bind 3d texture buffer
						glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObjectId);
						glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureId, 0);
						static const GLenum draw_buffers[] =
						{
							GL_COLOR_ATTACHMENT0
						};
						glDrawBuffers(1, draw_buffers);

						// clear the texture buffer
						glClear(GL_COLOR_BUFFER_BIT);

						Matrix4x4 m = Matrix4x4(Vector3(-1.0f), 2.0f);
						/*glLoadIdentity();
						glLoadMatrixf(m.data());*/
						glViewport(0, 0, 33, 33);

						//Matrix4x4 proj;
						//proj.Frustum(0.0f, 33.0f, 0.0f, 33.0f, 0.0f, 33.0f);


						// Build the model-view-projection matrix
						//Matrix4x4 modelToProj = entity->transform() * m.Inverse() * proj;

						// send the model-world matrix to the shader
						Matrix4x4 modelToWorld = Matrix4x4();
						modelToWorld.Translate(Vector3((float)i* (1.0f - 1.0f / 33.0f), (float)j* (1.0f - 1.0f / 33.0f), (float)k* (1.0f - 2.0f / 33.0f)));
						glUniformMatrix4fv(3, 1, GL_FALSE, modelToWorld.data());

						//glUniformMatrix4fv(_functionEvaluatorShader->get_uModelToWorld(), 1, GL_FALSE, entity->transform().data());
						glUniformMatrix4fv(4, 1, GL_FALSE, m.data());

						// configure our camera and viewport to render properly to the 3d texture
						/*
						float m[] = {
						2.0f, 0.0f, 0.0f, 0.0f,
						0.0f, 2.0f, 0.0f, 0.0f,
						0.0f, 0.0f, 2.0f, 0.0f,
						-1.0f, -1.0f, -1.0f, 1.0f,
						};
						*/


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

						//glUniform1i(textureId, 0);
						glUniform1i(_blockShader->get_uTextureArray(), textureId);
						glActiveTexture(GL_TEXTURE0);
						glBindTexture(GL_TEXTURE_2D_ARRAY, textureId);

						// turn off linear texture interpolation so we can sample the texture correctly
						glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
						glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
						glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP);
						glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP);


						// resets all the transformations
						glLoadIdentity();

						modelToWorld = Matrix4x4();
						modelToWorld.Translate(Vector3((float)i, (float)j, (float)k * (1.0f - (1.0f / 33.0f))));

						// Build the model-view-projection matrix
						Matrix4x4 modelViewProj = modelToWorld * _currentCamera->transform().Inverse() * GetProjectionMatrix();

						// send the model-view-projection matrix to the shader
						glUniformMatrix4fv(_blockShader->get_uModelToProjection(), 1, GL_FALSE, modelViewProj.data());
						glUniformMatrix4fv(7, 1, GL_FALSE, modelToWorld.data());
						Vector3 camPos = _currentCamera->transform().getPosition();
						glUniform3f(8, camPos.x(), camPos.y(), camPos.z());


						// enable block vertex buffer
						glBindBuffer(GL_ARRAY_BUFFER, _blockVertexBufferID);
						glEnableVertexAttribArray(_blockShader->Get_aPositionVertex());
						glVertexAttribPointer(_blockShader->Get_aPositionVertex(), 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), 0);

						// Pass the lookup tables to the shader
						glUniform1uiv(_blockShader->get_uCaseToNumpolys(), 256, case_to_numpolys);
						//glUniform1iv(_blockShader->get_uEdgeConnectList(), 3840, edge_connect_list);

						/*glBindBuffer(GL_UNIFORM_BUFFER, ubo);
						glBufferData(GL_UNIFORM_BUFFER, sizeof(edge_table), &(edge_table), GL_DYNAMIC_DRAW);	*/


						// execute drawing shader
						glDrawArrays(GL_POINTS, 0, 32 * 32 * 32);
					}
				}
			}
		}
	};
}