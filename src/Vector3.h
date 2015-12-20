namespace engine
{
	typedef struct
	{
		GLfloat x, y, z;

	}Vector3;

	Vector3 MakeVector3(GLfloat x, GLfloat y, GLfloat z)
	{
		Vector3 newVector;
		newVector.x = x;
		newVector.y = y;
		newVector.z = z;

		return newVector;
	}

	Vector3 NormalizeVector3(Vector3 vector)
	{
		GLdouble magnitude = sqrt(vector.x* vector.x + vector.y*vector.y + vector.z*vector.z);

		Vector3 unitVector;
		unitVector.x = vector.x / magnitude;
		unitVector.y = vector.y / magnitude;
		unitVector.z = vector.z / magnitude;

		return unitVector;
	}

	Vector3 AddVector3(Vector3 a, Vector3 b)
	{
		Vector3 newVector;
		newVector.x = a.x + b.x;
		newVector.y = a.y +b.y;
		newVector.z = a.z + b.z;

		return newVector;
	}

	Vector3 scalarMultiplyVector3(Vector3 vectorToMultiply, GLfloat scalar)
	{
		return MakeVector3(vectorToMultiply.x * scalar, vectorToMultiply.y * scalar, vectorToMultiply.z * scalar);
	}

	Vector3 SubstractVector3(Vector3 a, Vector3 b)
	{
		Vector3 newVector;
		newVector.x = a.x - b.x;
		newVector.y = a.y - b.y;
		newVector.z = a.z - b.z;

		return newVector;
	}
}