namespace engine
{
	class Entity
	{
		Matrix4x4 _transform;

		// Physics properties
		Vector3 _velocity;		
		Vector3 _rotationVelocity;			

		// Possible components
		VertexBuffer *_vertexBuffer;
		Renderer *_renderer;

	public:				

		Entity(VertexBuffer *vertexBuffer, Matrix4x4 transform) :
			_vertexBuffer(vertexBuffer), _transform(transform), _renderer(nullptr)
		{

		}

		~Entity()
		{
			
		}		

		Renderer* GetRenderer()
		{
			return _renderer;
		}

		void SetRenderer(Renderer *newRenderer)
		{
			_renderer = newRenderer;
		}

		VertexBuffer* GetVertexBuffer()
		{
			return _vertexBuffer;
		}

		void SetVertexBuffer(VertexBuffer *newVertexBuffer)
		{
			_vertexBuffer = newVertexBuffer;
		}

		// set transform
		Matrix4x4& transform()
		{
			return _transform;
		}

		Matrix4x4 transform() const
		{
			return _transform;
		}		

		Vector3 GetVelocity()
		{
			return _velocity;
		}

		void SetVelocity(Vector3 newVelocity)
		{
			_velocity = newVelocity;
		}		

		Vector3 GetRotationVelocity()
		{
			return _rotationVelocity;
		}

		void SetRotationVelocity(Vector3 newVelocity)
		{
			_rotationVelocity = newVelocity;
		}		

		void Render()
		{
			if (_renderer != nullptr)
				_renderer->Render(this);
		}
	};
}