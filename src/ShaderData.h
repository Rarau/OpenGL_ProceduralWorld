namespace engine
{
	class ShaderData
	{
	private:
		Vector4 _uColorValue;
		Vector3 _uLightPosition;
	public:
		Vector4 Get_uColorValue()
		{
			return _uColorValue;
		}

		void Set_uColorValue(Vector4 newColor)
		{
			_uColorValue = newColor;
		}

		Vector3 Get_uLightPosition()
		{
			return _uLightPosition;
		}

		void Set_uLightPosition(Vector3 newPosition)
		{
			_uLightPosition = newPosition;
		}

		ShaderData(Vector4 newColor, Vector3 newPosition):
		_uColorValue(newColor), _uLightPosition(newPosition)
		{

		}

		~ShaderData()
		{

		}
	};

}