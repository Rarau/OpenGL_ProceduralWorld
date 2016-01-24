namespace engine
{	

	//This class is responsible of tracking all our resources
	class ResourceManager
	{

	private:

		std::vector<engine::ShaderInterface*> *_shaderArray;
		std::vector<engine::VertexBuffer*> *_vertexBufferArray;
		std::vector<engine::Renderer*> *_rendererArray;

		ShaderData *_shaderData;

		ResourceManager()
		{
			_shaderArray = new std::vector<engine::ShaderInterface*>();
			_vertexBufferArray = new std::vector<engine::VertexBuffer*>();
			_rendererArray = new std::vector<engine::Renderer*>();


			// temporal --------------- 
			// TO-DO: delete this part as it is hardcoded -> createShader(), createGeometry()

			// add shaders:			
			ShaderInterface *shader = new ShaderInterface("Assets/Shaders/ColorVertexShader.glsl", 
														  "Assets/Shaders/ColorFragmentShader.glsl");
			_shaderArray->push_back(shader);
			
			ShaderInterface *lightShader = new ShaderInterface("Assets/Shaders/SimpleLightVertexShader.glsl",
															   "Assets/Shaders/SimpleLightFragmentShader.glsl");
			_shaderData = new ShaderData(Vector4(0.30f, 0.10f, 0.80f, 1.0f), Vector3(-1.0f, 1.0f, 1.0f));
			_shaderArray->push_back(lightShader);	

			

			// add geometry:
			// cube with simple light shader
			engine::VertexBuffer *sphereVertexBuffer = new engine::VertexBuffer(
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
			_vertexBufferArray->push_back(sphereVertexBuffer);

			

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

			for (std::vector<engine::Renderer*>::iterator rendererIterator = _rendererArray->begin();
				rendererIterator != _rendererArray->end(); rendererIterator++)
			{
				delete *rendererIterator;
			}
			delete _rendererArray;
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

		std::vector<Renderer*>* GetRendererArray()
		{
			return _rendererArray;
		}

		static ResourceManager& GetResourceManager()
		{
			static ResourceManager* resourceManager = nullptr;

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