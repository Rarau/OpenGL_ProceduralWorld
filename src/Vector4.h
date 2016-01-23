namespace engine
{
	typedef struct
	{
		GLfloat x;
		GLfloat y;
		GLfloat z;
		GLfloat w;

	} Vector4;

	Vector4 makeVector4(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
	{
		Vector4 newVector;
		newVector.x = x;
		newVector.y = y;
		newVector.z = z;
		newVector.w = w;

		return newVector;
	}

	Vector3 scalarMultiplyVector4(Vector3 vectorToMultiply, GLfloat scalar)
	{
		return MakeVector3(vectorToMultiply.x * scalar, vectorToMultiply.y * scalar, vectorToMultiply.z * scalar);
	}
}