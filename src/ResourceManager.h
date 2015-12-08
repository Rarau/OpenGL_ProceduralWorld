namespace engine
{
	//This class is responsible of tracking all our resources
	class ResourceManager
	{
	private:
		std::vector<engine::ShaderInterface*> *_shaderArray;
		std::vector<engine::VertexBuffer*> *_vertexBufferArray;

		ResourceManager()
		{
			_shaderArray = new std::vector<engine::ShaderInterface*>();
			_vertexBufferArray = new std::vector<engine::VertexBuffer*>();


			// temporal --------------- TO-DO: delete this part as it is hardcoded
			// add shaders:			
			ShaderInterface *shader = new ShaderInterface("Assets/Shaders/ColorVertexShader.txt", 
															"Assets/Shaders/ColorFragmentShader.txt");
			_shaderArray->push_back(shader);
			ShaderInterface *lightShader = new ShaderInterface("Assets/Shaders/SimpleLightVertexShader.txt", 
															"Assets/Shaders/SimpleLightFragmentShader.txt",
															"Assets/Shaders/PassThroughGeometryShader.txt");

			_shaderArray->push_back(lightShader);

			// add geometry
			// cube with simple light shader
			engine::VertexBuffer *cubeVertexBuffer = new engine::VertexBuffer(
				engine::cubeVertices, 
				sizeof(engine::cubeVertices), 
				GL_TRIANGLES, 
				36, 
				sizeof(GLfloat) * 3, 
				_shaderArray->at(1), 
				(GLvoid*)(offsetof(VertexDataPN, positionCoordinates)), 
				(GLvoid*)(offsetof(VertexDataPN, normalCoordinates))
			);

			_vertexBufferArray->push_back(cubeVertexBuffer);
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