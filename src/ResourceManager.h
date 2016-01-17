namespace engine
{
	//This class is responsible of tracking all our resources
	class ResourceManager
	{

	private:

		std::vector<engine::ShaderInterface*> *_shaderArray;
		std::vector<engine::VertexBuffer*> *_vertexBufferArray;

		ShaderData *_shaderData;

		ResourceManager()
		{
			_shaderArray = new std::vector<engine::ShaderInterface*>();
			_vertexBufferArray = new std::vector<engine::VertexBuffer*>();


			// temporal --------------- TO-DO: delete this part as it is hardcoded
			// add shaders:			
			ShaderInterface *shader = new ShaderInterface("Assets/Shaders/ColorVertexShader.txt", 
															"Assets/Shaders/ColorFragmentShader.txt");
			_shaderArray->push_back(shader);
			/*ShaderInterface *lightShader = new ShaderInterface("Assets/Shaders/SimpleLightVertexShader.txt", 
															"Assets/Shaders/SimpleLightFragmentShader.txt",
															"Assets/Shaders/PassThroughGeometryShader.txt");*/
			ShaderInterface *lightShader = new ShaderInterface("Assets/Shaders/SimpleLightVertexShader.txt",
				"Assets/Shaders/SimpleLightFragmentShader.txt");
			_shaderData = new ShaderData(makeVector4(0.30f, 0.10f, 0.80f, 1.0f), MakeVector3(-1.0f, 1.0f, 1.0f));
			_shaderArray->push_back(lightShader);

			// Instanced Rendering shader
			ShaderInterface *instanceShader = new ShaderInterface("Assets/Shaders/InstancedVertexShader.txt",
				"Assets/Shaders/InstancedFragmentShader.txt",
				"Assets/Shaders/InstancedGeometryShader.txt");
			_shaderArray->push_back(instanceShader);

			// add geometry
			// cube with simple light shader
			engine::VertexBuffer *cubeVertexBuffer = new engine::VertexBuffer(
				engine::sphereVertices, 
				sizeof(engine::sphereVertices), 
				GL_TRIANGLES, 
				2880, 
				sizeof(VertexDataPN),
				_shaderArray->at(1), 
				_shaderData,
				(GLvoid*)(offsetof(VertexDataPN, positionCoordinates)), 
				(GLvoid*)(offsetof(VertexDataPN, normalCoordinates))
			);
			
			_vertexBufferArray->push_back(cubeVertexBuffer);

			engine::VertexBuffer *quadVertexBuffer = new engine::VertexBuffer(
				engine::quadVertices,
				sizeof(engine::quadVertices),
				GL_TRIANGLES,
				6,
				sizeof(VertexDataP),
				_shaderArray->at(2),
				_shaderData,
				0,
				0
				);
			_vertexBufferArray->push_back(quadVertexBuffer);


			VertexDataP *blockPoints = GenerateSamplingPoints();
			engine::VertexBuffer *blockVertexBuffer = new engine::VertexBuffer(
				blockPoints,
				sizeof(VertexDataP) * 32 * 32 * 32,
				GL_POINTS,
				32 * 32 * 32,
				sizeof(VertexDataP),
				_shaderArray->at(0),
				_shaderData,
				0,
				0
				);
			_vertexBufferArray->push_back(blockVertexBuffer);

			// temporal ---------------
		}

		~ResourceManager()
		{
			for (std::vector<engine::ShaderInterface*>::iterator shaderIterator = _shaderArray->begin();
				shaderIterator != _shaderArray->end(); shaderIterator++)
			{
				delete *shaderIterator;
			}
			delete _shaderArray;

			for (std::vector<engine::VertexBuffer*>::iterator vertexIterator = _vertexBufferArray->begin();
				vertexIterator != _vertexBufferArray->end(); vertexIterator++)
			{
				delete *vertexIterator;
			}
			delete _vertexBufferArray;
		}

	public:

		std::vector<ShaderInterface*>* GetShaderArray()
		{
			return _shaderArray;
		}

		std::vector<VertexBuffer*>* GetVertexBufferArray()
		{
			return _vertexBufferArray;
		}

		static ResourceManager& GetResourceManager()
		{
			static ResourceManager *resourceManager = nullptr;

			if (resourceManager == nullptr)
			{
				resourceManager = new ResourceManager();
			}
			return *resourceManager;
		}

		static void DestroyResourceManager()
		{
			ResourceManager *resourceManager = &GetResourceManager();
			delete resourceManager;
		}

	};
}