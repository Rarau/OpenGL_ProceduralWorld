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

	Vector3 AddVector3(Vector3 a, Vector3 b)
	{
		Vector3 newVector;
		newVector.x = a.x + b.x;
		newVector.y = a.y +b.y;
		newVector.z = a.z + b.z;

		return newVector;
	}
}