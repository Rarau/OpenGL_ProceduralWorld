namespace engine
{
	class Entity
	{
	private:
		engine::VertexBuffer *_vertexBuffer;

		//TO-DO: change this for a 4x4 transformation matrix
		Vector3 _position;
		Vector3 _scale;
		Vector3 _rotation; //euler angles

		Vector3 _velocity;
		Vector3 _scaleVelocity;
		Vector3 _rotationVelocity;

		//for implementing lookAt method
		Vector3 _eyeVector;
		Vector3 _upVector;
		Vector3 _rightVector;		

		// Possible components
		Renderer *_renderer;

	public:		

		

		Entity(VertexBuffer *vertexBuffer, Vector3 position) :
			_vertexBuffer(vertexBuffer), _position(position), _scale(MakeVector3(1.0f, 1.0f, 1.0f)), _rotation(MakeVector3(0.0f, 0.0f, 0.0f)),
			_velocity(MakeVector3(0.0f, 0.0f, 0.0f)), _scaleVelocity(MakeVector3(0.0f, 0.0f, 0.0f)), _rotationVelocity(MakeVector3(0.0f, 0.0f, 0.0f)),
			_eyeVector(MakeVector3(0.0f, 0.0f, 0.0f)), _upVector(MakeVector3(0.0f, 1.0f, 0.0f)), _rightVector(MakeVector3(1.0f, 0.0f, 0.0f)), _renderer(nullptr)
		{

		}

		~Entity()
		{
			delete _renderer;
		}

		void SetRenderer(Renderer *newRenderer)
		{
			_renderer = newRenderer;
		}

		VertexBuffer *GetVertexBuffer()
		{
			return _vertexBuffer;
		}

		void SetVertexBuffer(VertexBuffer *newVertexBuffer)
		{
			_vertexBuffer = newVertexBuffer;
		}

		Vector3 GetPosition()
		{
			return _position;
		}

		void SetPosition(Vector3 newPosition)
		{
			_position = newPosition;
		}		

		Vector3 GetScale()
		{
			return _scale;
		}

		void SetScale(Vector3 newScale)
		{
			_scale = newScale;
		}

		Vector3 GetRotation()
		{
			return _rotation;
		}

		void SetRotation(Vector3 newRotation)
		{
			_rotation = newRotation;
		}

		Vector3 GetVelocity()
		{
			return _velocity;
		}

		void SetVelocity(Vector3 newVelocity)
		{
			_velocity = newVelocity;
		}

		Vector3 GetScaleVelocity()
		{
			return _scaleVelocity;
		}

		void SetScaleVelocity(Vector3 newVelocity)
		{
			_scaleVelocity = newVelocity;
		}

		Vector3 GetRotationVelocity()
		{
			return _rotationVelocity;
		}

		void SetRotationVelocity(Vector3 newVelocity)
		{
			_rotationVelocity = newVelocity;
		}

		Vector3 GetEyeVector()
		{
			return _eyeVector;
		}

		void SetEyeVector(Vector3 newVector)
		{
			_eyeVector = newVector;
		}

		Vector3 GetUpVector()
		{
			return _upVector;
		}

		void SetUpVector(Vector3 newVector)
		{
			_upVector = newVector;
		}

		Vector3 GetRightVector()
		{
			return _rightVector;
		}

		void SetRightVector(Vector3 newVector)
		{
			_rightVector = newVector;
		}

		void Render()
		{
			if (_renderer != nullptr)
				_renderer->Render(this);
		}
	};
}